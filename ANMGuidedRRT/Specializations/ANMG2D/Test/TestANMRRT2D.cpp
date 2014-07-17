#include "TestANMRRT2D.h"


/*-----------------------------------------------------------
Function: TestANMRRT2D::TestANMRRT2D()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestANMRRT2D::TestANMRRT2D(){
	Test::create("");
}

/*-----------------------------------------------------------
Function: TestANMRRT2D::TestANMRRT2D(string name)

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestANMRRT2D::TestANMRRT2D(string name){
	test_name = name;
}


/*-----------------------------------------------------------
Function: TestANMRRT2D:~TestANMRRT2D()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestANMRRT2D::~TestANMRRT2D(){
}

/*-----------------------------------------------------------
Function:void TestANMRRT2D::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestANMRRT2D::init(){
}




bool TestANMRRT2D::test_tree_scenario	(char* field, char* back, char* result,
									char* basefile, int expansion, int steps,
									int startx, int starty, int goalx, int goaly,
									unsigned int number_of_modes,
									char* random_file, bool erase){

	//-----------------------------------------------------
	// Setup RRT
	//-----------------------------------------------------
			RRTTools::File::convertBMPtoRRTField(string(back),string(field));

			RRTNode* goal = NULL;
			RRTNode* start = new RRTNode();
			ANMRRT2DConfiguration* start_conf = new ANMRRT2DConfiguration;
			// Generate a random vector
			vector<double> amplitudes_start,amplitudes_goal;
			srand(time(NULL));
			for(unsigned int i=0;i<number_of_modes;i++){
				amplitudes_start.push_back(((double)rand())/RAND_MAX);
				amplitudes_goal.push_back(((double)rand())/RAND_MAX);
			}
			start_conf->setX(startx);
			start_conf->setY(starty);
			start_conf->setAmplitudes(amplitudes_start);
			start->setDataP(start_conf);

			// To have a goal is mandatory now.
			// It doesn't need to store any amplitude as it does not need them, but they are
			// required to compute the distance so...
			goal = new RRTNode();
			ANMRRT2DConfiguration* goal_conf = new ANMRRT2DConfiguration;
			goal_conf->setX(goalx);
			goal_conf->setY(goaly);
			goal_conf->setAmplitudes(amplitudes_goal);
			goal->setDataP(goal_conf);

			// Metric for the RRT itself (based on amplitudes)
			ANMRRT2DMetric metric;
			metric.setTolerance(1);

			// Metric for completion check (based on coordinates)
			RRT2DMetric check_metric;
			metric.setTolerance(5);

			RRT2DColisionTest colTest(dynamic_cast<RRT2DMetric*>(&metric));
			colTest.setCollisionMap(field);

			ANMRRT2DExpansionAlgorithm expAlg(&metric);
			expAlg.setCollisionMapH(colTest.getCollisionMapH());
			expAlg.setCollisionMapW(colTest.getCollisionMapW());
			expAlg.setExpansionDistance(10);

			ANMRRT2DSamplingAlgorithm sampAlg;
			sampAlg.setCollisionMapH(colTest.getCollisionMapH());
			sampAlg.setCollisionMapW(colTest.getCollisionMapW());
			sampAlg.setDimension(number_of_modes);
			if(random_file != NULL) sampAlg.loadRandomNumbers(random_file);

			RRT2DNearestNeighbourAlgorithm nnAlg(dynamic_cast<RRT2DMetric*>(&metric));

			RRT2DCompletionCheck compCheck(&check_metric);
			compCheck.setMaxSteps(steps);
			compCheck.setGoal(goal);

			RRT2DSerializationAlgorithm rwAlg;
			rwAlg.setBaseFile(string(basefile));
			rwAlg.setBasePath(string(result));
			rwAlg.setFileType(string("txt"));
			rwAlg.setGoalNode(compCheck.getGoal());
			rwAlg.setMaxFiles(compCheck.getMaxSteps());
			rwAlg.setBackgroundImage(string(back));
			rwAlg.setWidth(colTest.getCollisionMapW());
			rwAlg.setHeight(colTest.getCollisionMapH());
			rwAlg.setClean(erase);
	//-----------------------------------------------------
	// End Setup
	//-----------------------------------------------------

	//--------------------
	// Init Normal Modes
	//--------------------
	ANMG2DNormalModeCalculator anmCalc(number_of_modes);
	anmCalc.calculateModes(dynamic_cast<ExpansionAlgorithm*>(&expAlg));

	//----------------------
	// Test the tree
	//----------------------
	RRT myRRT(
			dynamic_cast<RRTMetric*>(&metric),
			dynamic_cast<SamplingAlgorithm*>(&sampAlg),
			dynamic_cast<ExpansionAlgorithm*>( &expAlg),
			dynamic_cast<NearestNeighbourAlgorithm*>(&nnAlg),
			dynamic_cast<ColisionTest*>(&colTest),
			dynamic_cast<CompletionCheck*>(&compCheck),
			dynamic_cast<RRTSerializationAlgorithm*>(&rwAlg));

	myRRT.run(dynamic_cast<RRTNode*>(start));

	return true;
}


bool TestANMRRT2D::test_anmguided_scenario	(char* field, char* back, char* result,
									char* basefile, int expansion, int steps,int anmgsteps,
									int startx, int starty, int goalx, int goaly,
									unsigned int number_of_modes,
									char* random_file, bool erase){

	//-----------------------------------------------------
	// Setup RRT
	//-----------------------------------------------------
			RRTTools::File::convertBMPtoRRTField(string(back),string(field));


			RRTNode* start = new RRTNode();
			ANMRRT2DConfiguration* start_conf = new ANMRRT2DConfiguration;
			// Generate a random vector
			vector<double> amplitudes_start;
			srand(time(NULL));
			for(unsigned int i=0;i<number_of_modes;i++){
				amplitudes_start.push_back(((double)rand())/RAND_MAX);
			}
			start_conf->setX(startx);
			start_conf->setY(starty);
			start_conf->setAmplitudes(amplitudes_start);
			start->setDataP(start_conf);


			// Metric for the RRT itself (based on amplitudes and coordinates)
			ANMRRT2DMetric metric;
			metric.setTolerance(0);

			// Metric for completion check (based on coordinates)
			RRT2DMetric check_metric;
			check_metric.setTolerance(5);

			RRT2DColisionTest colTest(dynamic_cast<RRT2DMetric*>(&metric));
			colTest.setCollisionMap(field);

			ANMRRT2DExpansionAlgorithm expAlg(&metric);
			expAlg.setCollisionMapH(colTest.getCollisionMapH());
			expAlg.setCollisionMapW(colTest.getCollisionMapW());
			expAlg.setExpansionDistance(10);

			ANMRRT2DSamplingAlgorithm sampAlg;
			sampAlg.setCollisionMapH(colTest.getCollisionMapH());
			sampAlg.setCollisionMapW(colTest.getCollisionMapW());
			sampAlg.setDimension(number_of_modes);
			if(random_file != NULL) sampAlg.loadRandomNumbers(random_file);

			RRT2DNearestNeighbourAlgorithm nnAlg(dynamic_cast<RRT2DMetric*>(&metric));

			RRT2DCompletionCheck compCheck(&check_metric);
			compCheck.setMaxSteps(steps);

			RRT2DSerializationAlgorithm rwAlg;
			rwAlg.setBaseFile(string(basefile));
			rwAlg.setBasePath(string(result));
			rwAlg.setFileType(string("txt"));
			rwAlg.setGoalNode(compCheck.getGoal());
			rwAlg.setMaxFiles(compCheck.getMaxSteps()*anmgsteps);
			rwAlg.setBackgroundImage(string(back));
			rwAlg.setWidth(colTest.getCollisionMapW());
			rwAlg.setHeight(colTest.getCollisionMapH());
			rwAlg.setClean(erase);
			rwAlg.setSaveAllStates(false);

			RRT myRRT(
				dynamic_cast<RRTMetric*>(&metric),
				dynamic_cast<SamplingAlgorithm*>(&sampAlg),
				dynamic_cast<ExpansionAlgorithm*>( &expAlg),
				dynamic_cast<NearestNeighbourAlgorithm*>(&nnAlg),
				dynamic_cast<ColisionTest*>(&colTest),
				dynamic_cast<CompletionCheck*>(&compCheck),
				dynamic_cast<RRTSerializationAlgorithm*>(&rwAlg));

	//-----------------------------------------------------
	// End Setup
	//-----------------------------------------------------

	//----------------------------
	// Setup ANM guided algorithm
	//----------------------------
	RRTNode* goal = NULL;
	vector<double> amplitudes_goal;
	srand(time(NULL));
	for(unsigned int i=0;i<number_of_modes;i++){
		amplitudes_goal.push_back(((double)rand())/RAND_MAX);
	}
	goal = new RRTNode();
	ANMRRT2DConfiguration* goal_conf = new ANMRRT2DConfiguration;
	goal_conf->setX(goalx);
	goal_conf->setY(goaly);
	goal_conf->setAmplitudes(amplitudes_goal);
	goal->setDataP(goal_conf);

	ANMG2DNormalModeCalculator normCalc(number_of_modes);

	ANMG2DSerializationAlgorithm anmgSerAlg;
	anmgSerAlg.setTreeSerializer(dynamic_cast<RRTSerializationAlgorithm*>(&rwAlg));

	ANMG2DStartNodePicker startPick(dynamic_cast<RRTMetric*>(&check_metric));
	startPick.setGoal(goal);

	RRT2DCompletionCheck anmgCompCheck(&check_metric);
	anmgCompCheck.setMaxSteps(anmgsteps);
	anmgCompCheck.setGoal(goal);

	ANMGuidedRRT myANMguidedRRT(
						&myRRT,
						dynamic_cast<NormalModeCalculator*>(&normCalc),
						dynamic_cast<RRTMetric*>(&check_metric),
						dynamic_cast<StartNodePicker*> (&startPick),
						dynamic_cast<CompletionCheck*>(&anmgCompCheck),
						dynamic_cast<RRTSerializationAlgorithm*>(&anmgSerAlg)
						);

	myANMguidedRRT.run(dynamic_cast<RRTNode*>(start));

	return true;
}

/* -----------------------------------------------------------
Function: void TestANMRRT2D::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestANMRRT2D::run(){
	Test::run();
	//----------------------------------------------------



	/*TEST_FUNCTION(test_tree_scenario,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										"src/PathPlanning/ANMGuidedRRT/Specializations/ANMG2D/Test/Out",
										"anmrrt2d_test_with_goal_naive_1", 10, 500,
										61,36,
										610,370,10,
										NULL,true);*/

	TEST_FUNCTION(test_anmguided_scenario,
										  // description of the field
										  "src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										  // image representing the field
										  "src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										  // base path
										  "src/PathPlanning/ANMGuidedRRT/Specializations/ANMG2D/Test/Out",
										  // base name of all files
										  "anmrrt2d_test_with_goal_naive_1_",
										  // expansion distance
										  10,
										  // number of RRT steps
										  50,
										  // number of ANM guided RRT steps
										  10,
										  // start position
										  61, 36,
										  // end position
										  610, 370,
										  // number of modes to be calculated (fake modes)
										  2,
										  // path to load random numbers
										  NULL,
										  // clean temp files?
										  false);


	//-----------------------------------------------------
	finish();
}

/* -----------------------------------------------------------
Function: void TestANMRRT2D::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestANMRRT2D::finish(){

	//-----------------------------------------------------



	//-----------------------------------------------------
	Test::finish();
}


