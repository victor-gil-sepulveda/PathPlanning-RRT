/*
Files: TestANMProteinRRT.h TestANMProteinRRT.cpp

Started: 21/09/10

Description: Test Suite for PDBReader and PDBWriter classes.

*/

#ifndef TestANMProteinRRT_H_
#define TestANMProteinRRT_H_

#include "../../../../../../Tools/TestTools.h"
#include "../ANMProteinRRTExpansionAlgorithm.h"
#include "../../../../../../Molecules/ComplexBuilder.h"
#include "../../../../../../ANM/ANMCalculator.h"
#include "../../../../../../Minimizers/MinimizerBuilder.h"
#include "../../../../../../ANM/ANMCalculatorBuilder.h"
#include "../../../../../../ANM/ANMCalculator.h"
#include "../../../../../../System/System.h"
#include "../../../../../../Molecules/Complex.h"
#include "../../../../../../Molecules/Solvent/SolventGenerator.h"
#include "../../../../../Tools/Math/Solver.h"
#include "../../../../../../Tools/Assertion.h"
#include "../../../../../Tools/PathPlanningGeneralTools.h"
#include "../Metrics/AngularWeightMetric.h"
#include "../ANMProteinRRTSamplingAlgorithm.h"
#include "../Metrics/CartesianWeightMetric.h"

class TestANMProteinRRT : public Test{

	public:

		TestANMProteinRRT();

		TestANMProteinRRT(string name);

		virtual ~TestANMProteinRRT();

		void run();

		void init();

	private:

		void finish();

		//---------------------------
		// Global vars for all tests
		//---------------------------

		//---------------------------


		//---------------------------
		// Test Functions
		//---------------------------

		bool test_rrt_build();
		bool test_solve_weights();
		bool test_expansion();
		bool test_sampling();
		bool test_angular_weight_metric();
		bool test_cartesian_weight_metric();

		//---------------------------

};

#endif
