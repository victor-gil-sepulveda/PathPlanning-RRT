/*
 * Solver.h
 *
 *  Created on: 22/06/2011
 *      Author: victor
 */

#ifndef SOLVER_H_
#define SOLVER_H_


#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

#include "MatrixOps.h"
#include "ASA_CG/asa_user.h"
#include "ASA_CG/asa_cg.h"


namespace SolverFunctions{
		double 		function_value		(asa_objective *asa);
		void 		function_grad		(asa_objective *asa);
		double 		function_valgrad 	(asa_objective *asa);
};



class Solver{

	public:
						Solver				(unsigned int totalModes, unsigned int modeSize);
		virtual 		~Solver				();

		void			solve				(double grad_tol = 1.e-8);
		void			solveProjections	(vector<double>&,vector<double>&,vector<double>&);

		unsigned int	getModeSize			() const;
		unsigned int 	getTotalModes		() const;
		double*			getEigenvectors		() const;
		double*			getWeights			() const;
		double*			getDistances		() const;
		double*			getLowerRange		() const;
		double*			getHigherRange		() const;
		double 			getDistModificator	() const;

		void 			setEigenVectors		(double*eigenv,unsigned int size, bool transpose=false);
		void 			setEigenvectors		(vector<vector<double> >& eigenv, bool transpose=false);
		void 			setDistances		(vector<double>& dists);
		void 			setDistances		(double *distances,unsigned int size);
		void 			setWeights			(vector<double>& we);
		void 			setWeights			(double *we, unsigned int size);
		void 			setLowerRange		(double *lr, unsigned int size);
		void 			setLowerRange		(double lr);
		void			setHigherRange		(double *hr, unsigned int size);
		void			setHigherRange		(double hr);
		void 			setDistModificator	(double dist_modificator);

	private:
		// eigenvectors matrix in column major form
		double* 		eig;

		// eigenvectors transpose (can be seen as the eigenvectors matrix in row major form)
		double* 		eigT;

		// Displacements
		double*			distances;

		// result
		double* 		weights;

		// Eigenvector and distances matrix multiplied by the transposed eigenvectors matrix
		bool 			eig_modified;
		bool 			dist_modified;

		// Dimension of the space from which the eigenvectors come
		unsigned int 	dimension;

		// size of the colum of the eigenvectors matrix
		unsigned int 	mode_size;

		// Total number of modes we are using (size of the row of the
		// eigenvectors matrix)
		unsigned int 	number_of_modes;

		// Box min vale and max value
		double* 		minvalues;
		double* 		maxvalues;

		asa_objective 	objective;

		double 			dist_modificator;

		bool 			initialize_copy		(const char* function_name, double*& local_vector, unsigned int size, unsigned int expected_size);
		void 			set_c_array			(const char* function_name, double*& local_vector, double* extern_vector,unsigned int size, unsigned int expected_size);
		void 			set_cpp_vector		(const char* function_name, double*& local_vector, vector<double>& extern_vector,unsigned int size, unsigned int expected_size);
};

#endif /* SOLVER_H_ */
