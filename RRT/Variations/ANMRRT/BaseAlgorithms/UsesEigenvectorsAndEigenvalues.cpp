/*
 * UsesEigenvectorsAndEigenvalues.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "UsesEigenvectorsAndEigenvalues.h"

UsesEigenvectorsAndEigenvalues::UsesEigenvectorsAndEigenvalues(){

}

UsesEigenvectorsAndEigenvalues::~UsesEigenvectorsAndEigenvalues(){

}

vector<double>& UsesEigenvectorsAndEigenvalues::getEigenvalues() {
    return this->eigenvalues;
}

vector<vector<double> >& UsesEigenvectorsAndEigenvalues::getEigenvectors() {
    return this->eigenvectors;
}

void UsesEigenvectorsAndEigenvalues::setEigenvalues(vector<double>& values){
    copy(values.begin(),values.end(), this->eigenvalues.begin());
}

void UsesEigenvectorsAndEigenvalues::setEigenvalues(double *values, unsigned int dimension, unsigned int size){
	if(!(size%dimension))cout<<"[ ERROR UsesEigenvectorsAndEigenvalues::setEigenvalues] the size of the vector is not multiple of the dimension"<<endl;
	eigenvalues.clear();
	for(unsigned int i = 0; i < size; ++i){
		eigenvalues.push_back(values[i]);
	}
}

void UsesEigenvectorsAndEigenvalues::setEigenvectors(vector<vector<double> >& vectors){
	copy(vectors.begin(),vectors.end(), this->eigenvectors.begin());
}

void UsesEigenvectorsAndEigenvalues::setEigenvectors(double *vectors, unsigned int dimension, unsigned int size){
	if(!(size%dimension))cout<<"[ ERROR UsesEigenvectorsAndEigenvalues::setEigenvectors] the size of the vector is not multiple of the dimension"<<endl;
	eigenvectors.clear();
	eigenvectors.resize(size);
	for(unsigned int i = 0; i < size/dimension; ++i){
		for(unsigned int j = 0;j<dimension;++j){
			eigenvectors[i].push_back(vectors[i]);
		}
	}
}






