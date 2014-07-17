/*
 * ANMRRT2DConfiguration.cpp
 *
 *  Created on: Jun 8, 2011
 *      Author: vgil
 */

#include "ANMRRT2DConfiguration.h"

ANMRRT2DConfiguration::ANMRRT2DConfiguration():RRT2DConfiguration() {

}

ANMRRT2DConfiguration::~ANMRRT2DConfiguration() {
}

vector<double>& ANMRRT2DConfiguration::getAmplitudes(){
    return amplitudes;
}

void ANMRRT2DConfiguration::setAmplitudes(vector<double>& amp){
	this->amplitudes.clear();
	this->amplitudes.resize(amp.size());
    std::copy(amp.begin(),amp.end(),this->amplitudes.begin());
}


