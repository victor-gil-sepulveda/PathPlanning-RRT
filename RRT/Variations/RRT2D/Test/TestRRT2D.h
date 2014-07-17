/*
Files: TestRRT2D.h TestRRT2D.cpp

Started: 04/08/10

Description: Test Class for Atom Class testing.

*/

#ifndef TESTRRT2D_H_
#define TESTRRT2D_H_

#include "../../../../../Tools/TestTools.h"
#include "../../../../../Tools/Assertion.h"
#include "../../../RRT.h"
#include "../RRT2DColisionTest.h"
#include "../RRT2DExpansionAlgorithm.h"
#include "../RRT2DSamplingAlgorithm.h"
#include "../RRT2DMetric.h"
#include "../RRT2DSerializationAlgorithm.h"
#include "../RRT2DNearestNeighbourAlgorithm.h"
#include "../RRT2DCompletionCheck.h"
#include "../../../Tools/RRTTools.h"


class TestRRT2D : public Test{

	public:

		TestRRT2D();

		TestRRT2D(string name);

		virtual ~TestRRT2D();

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
		bool test_deterministic		();

		bool test_completion_check( double nodex, double nodey,
									double goalx,double goaly,
									int tolerance, double real_distance,
									bool check_result,
									bool verbose = false);

		bool test_run_scenario_1(const char* field, const char* back, const char* result,
								const char* basefile, int expansion, int steps,
								int startx,int starty, int goalx = -1, int goaly = -1,
								const char* random_file = NULL, bool erase = true);
		//---------------------------

};

#endif /* TESTRRT2D_H_ */
