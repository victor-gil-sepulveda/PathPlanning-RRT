/*
Files: TestANMRRT2D.h TestANMRRT2D.cpp

Started: 04/08/10

Description: Test Class for Atom Class testing.

*/

#ifndef TestANMRRT2D_H_
#define TestANMRRT2D_H_

#include "../../../../../Tools/TestTools.h"
#include "../../../../../Tools/Assertion.h"





#include "../../../../RRT/RRT.h"
#include "../../../../RRT/Tools/RRTTools.h"

#include "../../../../RRT/Variations/ANMRRT/RRT2D/ANMRRT2DMetric.h"
#include "../../../../RRT/Variations/ANMRRT/RRT2D/ANMRRT2DConfiguration.h"
#include "../../../../RRT/Variations/ANMRRT/RRT2D/ANMRRT2DExpansionAlgorithm.h"
#include "../../../../RRT/Variations/ANMRRT/RRT2D/ANMRRT2DSamplingAlgorithm.h"

#include "../../../../RRT/Variations/RRT2D/RRT2DColisionTest.h"
#include "../../../../RRT/Variations/RRT2D/RRT2DNearestNeighbourAlgorithm.h"
#include "../../../../RRT/Variations/RRT2D/RRT2DSerializationAlgorithm.h"
#include "../../../../RRT/Variations/RRT2D/RRT2DMetric.h"
#include "../../../../RRT/Variations/RRT2D/RRT2DCompletionCheck.h"

#include "../ANMG2DNormalModeCalculator.h"
#include "../ANMG2DSerializationAlgorithm.h"
#include "../ANMG2DStartNodePicker.h"
#include "../../../ANMGuidedRRT.h"

class TestANMRRT2D : public Test{

	public:

		TestANMRRT2D();

		TestANMRRT2D(string name);

		virtual ~TestANMRRT2D();

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

		bool test_tree_scenario(char* field, char* back, char* result,
								char* basefile, int expansion, int steps,
								int startx,int starty, int goalx = -1, int goaly = -1,
								unsigned int number_of_modes = 10, char* random_file = NULL,
								bool erase = true);

		bool test_anmguided_scenario(char* field, char* back, char* result,
								char* basefile, int expansion, int steps,int anmgsteps,
								int startx,int starty, int goalx = -1, int goaly = -1,
								unsigned int number_of_modes = 10, char* random_file = NULL,
								bool erase = true);

		//---------------------------

};

#endif /* TestANMRRT2D_H_ */
