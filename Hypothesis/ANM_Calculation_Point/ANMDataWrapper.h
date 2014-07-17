/////////////////////////////////////////////////////////////////////////////
/// \file ANMDataExtractor.h
/// \brief Class used to generate different kinds of data from the ANM Calculator
///
/// \author vgil
/// \date 02/08/2011
/////////////////////////////////////////////////////////////////////////////

#ifndef ANMDATAEXTRACTOR_H_
#define ANMDATAEXTRACTOR_H_

#include <cstdlib>
#include <ctime>
#include "../../../ANM/ANMCalculator.h"
#include "../../../ANM/ANMAlgorithm.h"
#include "../../Tools/PathPlanningGeneralTools.h"
#include "../../Tools/Math/Solver.h"

class ANMDataWrapper {
	public:

		//********
		// SETUP
		//********
					ANMDataWrapper						(PathPlanning::Tools::ANMObjectsPackage& pack);
					~ANMDataWrapper						();

		void 		randomWeightInitialization			();
		void 		weightInitialization				(double value);

		void 		saveOldPoints						();
		void		saveEigenvectors					();

		//*********
		// ACTIONS
		//*********
		void 		compute								();
		void 		minimize							();

		//************
		// VAR GETTERS
		//************
		double* 		getInitialCoordinates				();
		double* 		getCurrentCoordinates				();
		double* 		getLastCoordinates					();
		double*			getElNetworkInitialCoords			();
		double*			getANMWeights						();
		unsigned int 	getNodesSize						();

		//***********
		// QUERIES
		//***********
		vector<double> 	solveWeights								();
		void			writeEigenvectors_octave					();
		double 			getEigenvectorsProjection					(double* current_eigenvectors);
		double 			getElasticNetworkEnergyCalculation			(double* en_coords, double* current_coords);
		double			getRMSD										(double* coords_one, double* coords_two, unsigned int num_nodes);
		double  		calcProjectionWithInitialEigenvectors		();
		vector<double>	smartCalcProjectionWithInitialEigenvectors	();
		vector<double>	calcDistanceProjections						();

		//*************
		// DATA SAVING
		//*************
		void		writePoints(string file, vector<Point>& points);
		void		writeVector(string file, double* vec,unsigned int vec_size);
		void 		writeVector_octave(string file, double* vec, unsigned int vec_size);

	private:

		// Coordinates
		double* 	initial_coordinates;
		double* 	current_coordinates;
		double* 	en_coordinates;
		double*		aux_coordinates;
		double* 	last_coordinates;

		void				save_coords					(double*& here);
		void				from_coords_to_points		(double* coords, unsigned int size, vector<Point>& points);


		// Eigenvectors
		double* 				initial_eigenvectors;
		unsigned int 			eigen_size;
		static double 	 		calc_projections			(double* v1, double*v2,unsigned int v12size,unsigned int num_of_vectors);
		static vector<double> 	calc_smart_projections		(double* v1, double*v2,unsigned int v12size,unsigned int num_of_vectors);
		static double 	 		calc_one_smart_projection	(double* v1, double*v2,unsigned int v12size,unsigned int num_of_vectors, unsigned int* related);

		ANMCalculator*		anmcalc;
		ANMAlgorithm* 		anmalg;
		ANM_Params*			anmparams;
		double* 			eigenvectors;
		Atom** 				atoms;
		unsigned int		atoms_size;

		Complex* 			complex;

		PathPlanning::Tools::ANMObjectsPackage* pack;

		vector<int> nodes;
		unsigned int nodesSize;


		// for testing purposes...
		friend class TestANMDataWrapper;
};

#endif /* ANMDATAEXTRACTOR_H_ */
