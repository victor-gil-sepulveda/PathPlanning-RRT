#include "TestRRT2D.h"


/*-----------------------------------------------------------
Function: TestRRT2D::TestRRT2D()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestRRT2D::TestRRT2D(){
	Test::create("");
}

/*-----------------------------------------------------------
Function: TestRRT2D::TestRRT2D(string name)

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestRRT2D::TestRRT2D(string name){
	test_name = name;
}


/*-----------------------------------------------------------
Function: TestRRT2D:~TestRRT2D()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestRRT2D::~TestRRT2D(){
}

/*-----------------------------------------------------------
Function:void TestRRT2D::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestRRT2D::init(){
}



bool TestRRT2D::test_deterministic(){
	// So... if we run two times a random algorithm with the same random numbers... it's going
	// to behave exactly in the same way

	test_run_scenario_1("src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
						"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
						"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
						"rrt2d_test_with_goal_naive_1", 20, 100,
						61,36,
						590,372,
						"/home/vgil/Desktop/C++/PELE-1.5/src/PathPlanning/RRT/Variations/RRT2D/Test/Data/random_2",
						false);

	test_run_scenario_1("src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
						"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
						"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
						"rrt2d_test_with_goal_naive_2", 20, 100,
						61,36,
						590,372,
						"/home/vgil/Desktop/C++/PELE-1.5/src/PathPlanning/RRT/Variations/RRT2D/Test/Data/random_2",
						false);

	system("rm src/PathPlanning/RRT/Variations/RRT2D/Test/Out/rrt2d_test_with_goal_naive_????.mpeg");
	system("rm src/PathPlanning/RRT/Variations/RRT2D/Test/Out/rrt2d_test_with_goal_naive_????.png");
	system("cat *1???.txt > 1.txt");
	system("cat *2???.txt > 2.txt");
	bool test = TestTools::exec("diff 1.txt 2.txt") == string("");
	system("rm 1.txt 2.txt *1???.txt *2???.txt");
	return test;
}


bool TestRRT2D::test_completion_check(	double nodex, double nodey,
										double goalx,double goaly,
										int tolerance, double real_distance,
										bool check_result, bool verbose){
	RRT2DMetric metric;
	metric.setTolerance(tolerance);

	RRTNode* node = new RRTNode();
	RRT2DConfiguration* node_conf = new RRT2DConfiguration;
	node_conf->setX(nodex);
	node_conf->setY(nodey);
	node->setDataP(node_conf);

	RRTNode* goal = new RRTNode();
	RRT2DConfiguration* goal_conf = new RRT2DConfiguration;
	goal_conf->setX(goalx);
	goal_conf->setY(goaly);
	goal->setDataP(goal_conf);

	RRT2DCompletionCheck compCheck(&metric);
	compCheck.setGoal(goal);

	bool result = Assertion::assertExpectedEqualsCalculatedWithinPrecision(real_distance,metric.calcDistance(node,goal),10e-2)
					&& (compCheck.checkCompletion(node) == check_result);

	if(verbose){
		cout<<"Result of distance calculation: "<< metric.calcDistance(node,goal)<<endl;
		cout<<"Result of overlapping check: "<< toString(compCheck.checkCompletion(node))<<endl;
	}

	delete node;
	delete goal;

	return result;
}


bool TestRRT2D::test_run_scenario_1(const char* field, const char* back, const char* result,
									const char* basefile, int expansion, int steps,
									int startx, int starty, int goalx, int goaly,
									const char* random_file, bool erase){

	RRTTools::File::convertBMPtoRRTField(string(back),string(field));

	RRTNode* goal = NULL;
	RRTNode* start = new RRTNode();
	RRT2DConfiguration* start_conf = new RRT2DConfiguration;
	start_conf->setX(startx);
	start_conf->setY(starty);
	start->setDataP(start_conf);

	if(goalx != -1 && goaly != -1){
		goal = new RRTNode();
		RRT2DConfiguration* goal_conf = new RRT2DConfiguration;
		goal_conf->setX(goalx);
		goal_conf->setY(goaly);
		goal->setDataP(goal_conf);
	}

	RRT2DMetric metric;
	metric.setTolerance(10);

	RRT2DColisionTest colTest(&metric);
	colTest.setCollisionMap(field);

	RRT2DExpansionAlgorithm expAlg(&metric);
	expAlg.setCollisionMapH(colTest.getCollisionMapH());
	expAlg.setCollisionMapW(colTest.getCollisionMapW());
	expAlg.setExpansionDistance(10);

	RRT2DSamplingAlgorithm sampAlg;
	sampAlg.setCollisionMapH(colTest.getCollisionMapH());
	sampAlg.setCollisionMapW(colTest.getCollisionMapW());
	sampAlg.setDimension(2);
	if(random_file != NULL) sampAlg.loadRandomNumbers(random_file);

	RRT2DNearestNeighbourAlgorithm nnAlg(&metric);

	RRT2DCompletionCheck compCheck(&metric);
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

/* -----------------------------------------------------------
Function: void TestRRT2D::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestRRT2D::run(){
	Test::run();
	//----------------------------------------------------


	//TEST_FUNCTION(test_deterministic);


	/*TEST_FUNCTION(test_completion_check , 	2, 2,
											2, 2,
											0, 0,
											true)

	TEST_FUNCTION(test_completion_check , 	2, 2,
											2, 2,
											10, 0,
											true)

	TEST_FUNCTION(test_completion_check , 	1, 1,
											50, 50,
											0, 69.296,
											false)

	TEST_FUNCTION(test_completion_check , 	1, 1,
											50, 50,
											10, 69.296,
											false)

	TEST_FUNCTION(test_completion_check , 	1, 1,
											50, 50,
											70, 69.296,
											true)

	TEST_FUNCTION(test_completion_check , 	1, 1,
											50, 50,
											68, 69.296,
											false)

	TEST_FUNCTION(test_completion_check , 	580, 359,
											590, 372,
											20, 16.401,
											true, true)

	TEST_FUNCTION(test_completion_check , 	589,359,
											590, 372,
											20, 13.0384,
											true, true)*/

/*	TEST_FUNCTION(test_run_scenario_1,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
										"rrt2d_test_no_goal_naive", 10, 200,
										61,36);*/

	// It is supposed to stop when node 40 is inserted
	/*TEST_FUNCTION(test_run_scenario_1,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
										"rrt2d_test_with_goal_naive_1", 20, 100,
										61,36,
										203,187,
										"/home/vgil/Desktop/C++/PELE-1.5/src/PathPlanning/RRT/Variations/RRT2D/Test/Data/random_2",
										true);*/

	TEST_FUNCTION(test_run_scenario_1,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
										"rrt2d_test_with_goal_naive_2", 10, 100,
										61,36,
										610,370,
										NULL,true);

	/*TEST_FUNCTION(test_run_scenario_1,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/field1.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/field1.jpeg",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
										"rrt2d_test_with_goal_naive_1_", 15, 5000,
										61,36,
										610,370);


	TEST_FUNCTION(test_run_scenario_1,	"src/PathPlanning/RRT/Variations/RRT2D/Test/Out/espiral.rrt",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Data/espiral.jpg",
										"src/PathPlanning/RRT/Variations/RRT2D/Test/Out",
										"rrt2d_test_goal_spiral", 10, 6000,
										500,40,
										304,285);*/

	//-----------------------------------------------------
	finish();
}

/* -----------------------------------------------------------
Function: void TestRRT2D::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestRRT2D::finish(){

	//-----------------------------------------------------



	//-----------------------------------------------------
	Test::finish();
}


