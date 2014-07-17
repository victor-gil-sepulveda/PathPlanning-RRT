/*
 * ANMG2DNormalModeCalculator.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "ANMG2DNormalModeCalculator.h"

ANMG2DNormalModeCalculator::ANMG2DNormalModeCalculator(unsigned int number_of_modes):NormalModeCalculator(number_of_modes){
	srand(time(NULL));
}

ANMG2DNormalModeCalculator::~ANMG2DNormalModeCalculator(){

}

void ANMG2DNormalModeCalculator::calculate_modes(ExpansionAlgorithm *exAlg){

	vector<vector<double> >& modes = dynamic_cast<ANMRRT2DExpansionAlgorithm*>(exAlg)->getEigenvectors();
	modes.clear();
	modes.resize(getNumberOfModes());

	// As this is a system of 1 particle, normal modes will be 2D and we will add an arbitrary number.
	for(unsigned int i =0;i<getNumberOfModes();++i){
		if(i%2!=1){
			double mode_x = rand();
			double mode_y = rand();
			mode_x = mode_x/(double)RAND_MAX;
			mode_y = mode_y/(double)RAND_MAX;

			double norm = sqrt(mode_x*mode_x + mode_y*mode_y);

			modes[i].push_back(mode_x/norm);
			modes[i].push_back(mode_y/norm);
		}
		else{
			// one of each 2 is orthogonal
			modes[i].push_back(modes[i-1][1]);
			modes[i].push_back(modes[i-1][0]);
		}
	}

	// Eigenvalues are not required indeed... so we do not generate them
}


