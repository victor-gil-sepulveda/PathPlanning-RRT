/*
 * ANMRRT2DMetric.cpp
 *
 *  Created on: Jun 8, 2011
 *      Author: vgil
 */

#include "ANMRRT2DMetric.h"

ANMRRT2DMetric::ANMRRT2DMetric() {
}

ANMRRT2DMetric::~ANMRRT2DMetric() {
}

double ANMRRT2DMetric::calc_distance(RRTNode *first, RRTNode *second){
	ANMRRT2DConfiguration* c1 = dynamic_cast<ANMRRT2DConfiguration*>(first->getData());
	ANMRRT2DConfiguration* c2 = dynamic_cast<ANMRRT2DConfiguration*>(second->getData());

	vector<double>& c1_amps = c1->getAmplitudes();
	vector<double>& c2_amps = c2->getAmplitudes();

	// Calc difference vector
	double sum = 0;
	for(unsigned int i =0;i<c1_amps.size();i++){
		sum += (c1_amps[i]-c2_amps[i])*(c1_amps[i]-c2_amps[i]);
	}

	double amp_norm = sqrt(sum);

	// The resulting ' metric' (not sure if this accomplishes the triangular
	// inequality) is a mixture of distance and aplitudes (weighted)
	return 0.6*amp_norm + 0.4*sqrt(pow(c1->getX()-c2->getX(),2)+pow(c1->getY()-c2->getY(),2));
}


