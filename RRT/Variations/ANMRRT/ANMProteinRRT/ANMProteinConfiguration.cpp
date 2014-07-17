/*
 * ANMProteinConfiguration.cpp
 *
 *  Created on: 11/06/2011
 *      Author: vgil
 */

#include "ANMProteinConfiguration.h"

BoundDescriptor::BoundDescriptor (unsigned int s){
	this->hirange = NULL;
	this->lowrange = NULL;
	this->size = s;
	hirange = (double*)  malloc(size*sizeof(double));
	lowrange = (double*) malloc(size*sizeof(double));

}


BoundDescriptor::BoundDescriptor (const BoundDescriptor& bd){
	*this= bd;
}

BoundDescriptor::~BoundDescriptor(){
	if(hirange) 	free( hirange);
	if(lowrange) 	free( lowrange);
}

BoundDescriptor& 	BoundDescriptor::operator=(const BoundDescriptor& other){
	memcpy(this->hirange , other.hirange ,size*sizeof(double));
	memcpy(this->lowrange, other.lowrange,size*sizeof(double));
	return *this;
}
void BoundDescriptor::setBoundaries(vector<double>& eigenvalues){
	double tmp[this->size];
	for(unsigned int i = 0; i < this->size;++i){
		tmp[i]= eigenvalues[i];
	}

	setBoundaries(tmp);
}

void	BoundDescriptor::setBoundaries	(double* eigenvalues){
	process_eigenvalues(eigenvalues);
}

double* BoundDescriptor::getUpperBound (){
	return hirange;
}

double* BoundDescriptor::getLowerBound (){
	return lowrange;
}


RangedBoundDescriptor::RangedBoundDescriptor(double lower, double upper, unsigned int size):BoundDescriptor(size){
	this->upper = upper;
	this->lower = lower;
}

RangedBoundDescriptor::RangedBoundDescriptor(const RangedBoundDescriptor& bd):BoundDescriptor(bd){
	*this = bd;
}

RangedBoundDescriptor::~RangedBoundDescriptor(){}

RangedBoundDescriptor& 	RangedBoundDescriptor::operator= (const RangedBoundDescriptor& other){
	*((BoundDescriptor*)(this)) = *((BoundDescriptor*)(&other));
	this->upper = upper;
	this->lower = lower;

	return *this;
}

void RangedBoundDescriptor::process_eigenvalues	(double* eigval){
	for(unsigned int i = 0; i < this->size;++i){
		hirange[i] = 	upper;
		lowrange[i] = 	lower;
	}
}

ANMProteinConfiguration::ANMProteinConfiguration(AtomSet* prot, ANMCalculator* 	calctor, BoundDescriptor* bd, vector<double>& w) :RRTProteinConfiguration(prot){
	this->anm_calculator = calctor;
	this->weights.resize(w.size());
	std::copy(w.begin(),w.end(),this->weights.begin());
	this->bounds = bd;
}

ANMProteinConfiguration::~ANMProteinConfiguration(){}

ANMCalculator* 	ANMProteinConfiguration::getANMCalculator (){
	return anm_calculator;
}

vector<double>&	ANMProteinConfiguration::getWeights(){
	return weights;
}

BoundDescriptor* ANMProteinConfiguration::getBoundaries	(){
	return bounds;
}

double* ANMProteinConfiguration::getUpperBound(){
	return bounds->getUpperBound();
}

double* ANMProteinConfiguration::getLowerBound(){
	return bounds->getLowerBound();
}
