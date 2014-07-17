/*
 * ANMRRT2DExpansionAlgorithm.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "ANMRRT2DExpansionAlgorithm.h"

ANMRRT2DExpansionAlgorithm::ANMRRT2DExpansionAlgorithm(ANMRRT2DMetric* m ):RRT2DExpansionAlgorithm(dynamic_cast<RRT2DMetric*>(m)){
}

ANMRRT2DExpansionAlgorithm::~ANMRRT2DExpansionAlgorithm(){
}


RRTNode* ANMRRT2DExpansionAlgorithm::do_expansion(RRTNode* from, RRTNode* to){
	ANMRRT2DConfiguration* c_from = dynamic_cast<ANMRRT2DConfiguration*>(from->getData());
	ANMRRT2DConfiguration* c_to = dynamic_cast<ANMRRT2DConfiguration*>(to->getData());
	ANMRRT2DConfiguration* c_expand = new ANMRRT2DConfiguration;

	double dist = getMetric()->calcDistance(from,to);

	if(dist > 0.7){
		double dir_x = 0;
		double dir_y = 0;

		vector<double>& amplitudes =  c_to->getAmplitudes();
		vector<vector<double> >& eigenvectors = getEigenvectors();
		for(unsigned int i = 0; i<amplitudes.size(); ++i){
			dir_x +=amplitudes[i]*eigenvectors[i][0];
			dir_y +=amplitudes[i]*eigenvectors[i][1];
		}

		// Normalize the direction
		double norm = sqrt(dir_x*dir_x + dir_y*dir_y);
		dir_x /= norm;
		dir_y /= norm;

		// Now generate the new coordinates
		double x_new = c_from->getX() + dir_x*getExpansionDistance();
		double y_new = c_from->getY() + dir_y*getExpansionDistance();

		if (x_new > (int)getCollisionMapW()) x_new = getCollisionMapW();
		if (x_new < 0) x_new = 0;

		if (y_new > (int)getCollisionMapH()) y_new = getCollisionMapH();
		if (y_new < 0) y_new = 0;

		// So now we have moved the point to (x_new,y_new), so maybe we have not used the
		// amplitudes we were supposed to have used.
		// In fact we are moving it about expans. dist / norm times each value of the amplitude
		double atenuation = getExpansionDistance()/norm;
		vector<double> new_amplitudes;
		for(unsigned int i = 0; i<amplitudes.size(); ++i){
			new_amplitudes.push_back(amplitudes[i]*atenuation);
		}

		c_expand->setX(x_new);
		c_expand->setY(y_new);
		c_expand->setAmplitudes(new_amplitudes);

		RRTNode* expanded = new RRTNode;
		expanded->setDataP(c_expand);

		return expanded;
	}
	else{
		delete c_expand;
		return NULL;
	}
}
