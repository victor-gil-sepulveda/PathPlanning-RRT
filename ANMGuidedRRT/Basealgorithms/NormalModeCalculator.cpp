/*
 * NormalModeCalculator.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "NormalModeCalculator.h"


NormalModeCalculator::NormalModeCalculator(unsigned int number_of_modes){
	setNumberOfModes(number_of_modes);
}

NormalModeCalculator::~NormalModeCalculator() {
}

void NormalModeCalculator::calculateModes(ExpansionAlgorithm *expAlg){
	calculate_modes(expAlg);
}

unsigned int NormalModeCalculator::getNumberOfModes() const
{
    return number_of_modes;
}

void NormalModeCalculator::setNumberOfModes(unsigned int numberOfModes)
{
    this->number_of_modes = numberOfModes;
}




