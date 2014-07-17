/*
 * UsesEigenvectorsAndEigenvalues.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef UsesEigenvectorsAndEigenvalues_H_
#define UsesEigenvectorsAndEigenvalues_H_

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class UsesEigenvectorsAndEigenvalues {
	public:
									UsesEigenvectorsAndEigenvalues	();
		virtual 					~UsesEigenvectorsAndEigenvalues	();

		vector<double> &			getEigenvalues				();
		vector<vector<double> >	&	getEigenvectors				();

		void 						setEigenvalues				(vector<double>& values);
		void 						setEigenvalues				(double* values, unsigned int dimension, unsigned int size);
		void 						setEigenvectors				(vector<vector<double> >& vectors);
		void 						setEigenvectors				(double* vectors, unsigned int dimension, unsigned int size);

	private:

		vector<vector<double> > 	eigenvectors;
		vector<double>				eigenvalues;
};

#endif /* UsesEigenvectorsAndEigenvalues_H_ */
