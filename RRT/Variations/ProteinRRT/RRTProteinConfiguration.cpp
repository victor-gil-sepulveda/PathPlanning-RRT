/*
 * ProteinConfiguration.cpp
 *
 *  Created on: 11/06/2011
 *      Author: vgil
 */

#include "RRTProteinConfiguration.h"

RRTProteinConfiguration::RRTProteinConfiguration(AtomSet* 	p): RRTConfiguration() {
	set_protein(p);
}

RRTProteinConfiguration::~RRTProteinConfiguration() {
	if(this->state_coordinates) free(this->state_coordinates);
}

double *RRTProteinConfiguration::getStateCoordinates(){
	return state_coordinates;
}

unsigned int RRTProteinConfiguration::getCoordinatesSize() const{
	return this->size_coordinates;
}

// Applies the coordinates to the protein and returns it (we are sharing this AtomSet with
// other nodes
AtomSet* RRTProteinConfiguration::getProtein(){
	this->protein->updateCartesianCoordinates(this->state_coordinates,this->size_coordinates);
	return this->protein;
}

// Sets the protein and stores its coordinates
void RRTProteinConfiguration::set_protein (AtomSet* p){
	this->protein = p;
	this->size_coordinates = p->getNumberOfAllAtoms();
	// Create space for the coordinates
	this->state_coordinates = (double*) malloc(this->size_coordinates*sizeof(double));
	memcpy(this->state_coordinates,p->getAllCartesianCoordinates(),this->size_coordinates*sizeof(double));
}

