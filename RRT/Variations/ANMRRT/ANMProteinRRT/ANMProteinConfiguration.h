/*
 * ANMProteinConfiguration.h
 *
 *  Created on: 11/06/2011
 *      Author: vgil
 */

#ifndef ANMPROTEINCONFIGURATION_H_
#define ANMPROTEINCONFIGURATION_H_

#include "../../ProteinRRT/RRTProteinConfiguration.h"
#include "../BaseAlgorithms/UsesEigenvectorsAndEigenvalues.h"
#include "../../../../../ANM/ANMCalculator.h"


// A bound descriptor is valid only for an ANMCalculator instance
class BoundDescriptor{
	public:
							BoundDescriptor		(unsigned int s);
							BoundDescriptor		(vector<double>& eigenvalues);
							BoundDescriptor		(const BoundDescriptor& bd);
				virtual 	~BoundDescriptor	();

		BoundDescriptor& 	operator=			(const BoundDescriptor& other);


		void				setBoundaries		(double* eigenvalues);
		void 				setBoundaries		(vector<double>& eigenvalues);

		double* 			getUpperBound		();
		double* 			getLowerBound		();


	protected:

		// Process eigenvalues to generate eigenvalues-related bounds
		virtual void 		process_eigenvalues	(double* eigval) = 0;


		double* 			hirange;
		double* 			lowrange;
		unsigned int 		size;
		ANMCalculator* 		anm_calculator;
};

class RangedBoundDescriptor: public BoundDescriptor{

	public:
					RangedBoundDescriptor(double lower, double upper, unsigned int size);
					RangedBoundDescriptor(const RangedBoundDescriptor& rbd);
					~RangedBoundDescriptor();
					RangedBoundDescriptor& 	operator=			(const RangedBoundDescriptor& other);

	private:

		void 		process_eigenvalues	(double* eigval);

		double 		upper;
		double 		lower;
};


class ANMProteinConfiguration: public RRTProteinConfiguration {

	public:
							ANMProteinConfiguration		(AtomSet* prot, ANMCalculator* 	calctor, BoundDescriptor* bd, vector<double>& w);
		virtual 			~ANMProteinConfiguration	();

		ANMCalculator* 		getANMCalculator			();
		vector<double>&		getWeights					();
		BoundDescriptor* 	getBoundaries				();
		double* 			getUpperBound 				();
		double*				getLowerBound				();

	private:

		// The calculator, bounds and weights have to be coherent. This coherence has to be maintained by the user.

		ANMCalculator* anm_calculator; 	//  This is shared,
									   	//	it stores the eigenvectors and directions, so it's part of the state.
		vector<double> 	weights;		// 	Weights that led us to this configuration (over the eigenvectors stored in the
										// 	anm_calculator
		BoundDescriptor* bounds;		// 	Max and min value each weight can have. Depends on the anmCalculator.
};

#endif /* ANMPROTEINCONFIGURATION_H_ */
