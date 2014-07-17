#include "TestANMProteinRRT.h"




/*-----------------------------------------------------------
Function: TestANMProteinRRT::TestANMProteinRRT()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestANMProteinRRT::TestANMProteinRRT(){
	Test::create("");
}

/* -----------------------------------------------------------
Function: TestANMProteinRRT::TestANMProteinRRT(string name)

Description:
Initializes the test class giving it a name.

In:
void

Out:
void
-----------------------------------------------------------------*/

TestANMProteinRRT::TestANMProteinRRT(string name){
	Test::create(name);
}

/*-----------------------------------------------------------
Function: TestANMProteinRRT:~TestANMProteinRRT()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestANMProteinRRT::~TestANMProteinRRT(){

}

/*-----------------------------------------------------------
Function:void TestANMProteinRRT::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestANMProteinRRT::init(){
}

bool TestANMProteinRRT::test_rrt_build(){

	return true;
}

bool TestANMProteinRRT::test_solve_weights(){

	// Define the dimension of a point
	unsigned int dimension = 3;

	//------------------------------------
	// Load a 3-residue peptide of alanine
	//------------------------------------
	System system;
	ComplexBuilder complexBuilder;
	Complex * complex = complexBuilder.build("src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb");
	Solvent* solvent = SolventGenerator::createSolvent(*complex,false);

	// Get the number of CA
	vector<Atom*> c_alphas = complex->getAtomsWithName(AtomNames::CA);
	unsigned int c_alphas_size = c_alphas.size();

	// Backup old points
	vector<Point> old_points;
	for(unsigned int i =0; i < c_alphas.size();++i){
		old_points.push_back(c_alphas[i]->toPoint());
	}


	//------------------------------------------
	//Create the Minimizer and ANM Calculator
	//------------------------------------------
	ConstraintParams * constraintParams;
	EnergyCalculator * energyCalculator;
	MinParams * anmMinParameters;
	Minimizer * anmMinimizer;

	string json_contents = Utils::fileToString("src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Data/anm_config.conf");

	Json::Value root;
	Json::Reader reader;

	bool parsedSuccess = reader.parse(json_contents, root, false);

	if(!parsedSuccess){
		cout << "Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
		exit(1);
	}

	Json::Value dummy_general_block;

	//	Json::Value & generalConfigurationBlock, Json::Value & jsonBlock,
	//							string defaultConfigurationPath, string sectionName

	// Parse ANM
	Json::Value jSonANMBlock 		= JsonUtils::searchSection(dummy_general_block, root,  JsonDefaultBlockPaths::EMPTY_PATH,
																	  Configuration_ANM::BLOCK_NAME);
	// Parse Minimizer
	Json::Value jSonMinimizerBlock 	= JsonUtils::searchSection(dummy_general_block, jSonANMBlock, JsonDefaultBlockPaths::EMPTY_PATH,
																		Configuration_ANM::MINIMIZER);

	MinimizerBuilder minimizerBuilder;
	minimizerBuilder.createFromConfiguration(jSonMinimizerBlock, dummy_general_block,solvent, &system,
											&constraintParams, &energyCalculator, &anmMinParameters,
													&anmMinimizer);
	ANM_Params * anmParameters;
	ANMCalculator * anmCalculator;
	ANMCalculatorBuilder anmCalculatorBuilder;
	anmCalculatorBuilder.createFromConfiguration(jSonANMBlock, NULL, NULL, NULL, &anmParameters, &anmCalculator);

	//---------------------------

	vector<double> weights;
//	weights.push_back(0.09252450);
//	weights.push_back(-0.01409195);
//	weights.push_back(0.112372);
	weights.push_back(0.8);
	weights.push_back(-0.45);
	weights.push_back(0.73);
//	weights.push_back(0.4);
//	weights.push_back(-0.0682);
//	weights.push_back(0.54);

	anmCalculator->getParameters()->setWeights(weights);

	cout<<"Computing ANM"<<flush<<endl;
	anmCalculator->compute(complex);

	cout<<"Minimizing"<<flush<<endl;
	anmCalculator->minimize(anmMinParameters,complex,energyCalculator,anmMinimizer);

	cout<<"Writing file"<<flush<<endl;
	PDBWriter::write("src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Temp/post_anm.pdb",*complex,PELEFORMAT);

	// Store new points (after ANM)
	vector<Point> new_points;
	for(unsigned int i =0; i < c_alphas.size();++i){
		new_points.push_back(c_alphas[i]->toPoint());
	}

	// Write Arrow descriptions
	/*cout<<"draw color white"<<endl<<"draw materials off"<<endl;
	for(unsigned int i =0; i < c_alphas_size; ++i){
		printf("draw line  { %8.3f %8.3f %8.3f } { %8.3f %8.3f %8.3f }\n",old_points[i].getX(),old_points[i].getY(),old_points[i].getZ(),
				new_points[i].getX(),new_points[i].getY(),new_points[i].getZ());
	}*/


	vector<Point> target_points;
	double* target = anmCalculator->getAnmTargetCoords();
	for(unsigned int i =0; i < c_alphas.size();++i){
		Point p(target[i*3],target[i*3+1],target[i*3+2]);
		target_points.push_back(p);
	}

	/*
	cout<<"draw color green"<<endl<<"draw materials off"<<endl;
	for(unsigned int i =0; i < c_alphas_size; ++i){
		printf("draw line  { %8.3f %8.3f %8.3f } { %8.3f %8.3f %8.3f }\n",old_points[i].getX(),old_points[i].getY(),old_points[i].getZ(),
				target_points[i].getX(),target_points[i].getY(),target_points[i].getZ());
	}*/

	vector<double> my_distances_to_target;
	for(unsigned int i =0; i < c_alphas_size; ++i){
		my_distances_to_target.push_back(target_points[i].distance(old_points[i]));
	}

	vector<double> my_distances_to_final;
	for(unsigned int i =0; i < c_alphas_size; ++i){
		my_distances_to_final.push_back(new_points[i].distance(old_points[i]));
	}

	for(unsigned int i =0; i < c_alphas_size; ++i){
		cout<<my_distances_to_target[i]<<" "<<my_distances_to_final[i]<<endl;
	}

	//---------------------------
	// Create a solver
	//---------------------------
	unsigned int number_of_modes = anmCalculator->getParameters()->getNumbermodes();
	unsigned int mode_size = c_alphas_size*dimension;

	/*cout<<"Vectors"<<endl;
	cout<<"{";
	double* eigen = anmCalculator->getEigenvectors();
	for (unsigned int i = 0; i < number_of_modes; ++i){
		cout<<"{";
		for (unsigned int j = 0; j < mode_size; ++j){
			cout<<eigen[i*mode_size+j]<<",";
		}
		cout<<"},";
	}
	cout<<"}";
	exit(1);*/

	Solver solver(number_of_modes, mode_size);

	// Add them to the solver
	solver.setHigherRange(10);
	solver.setLowerRange(-10);

	solver.setEigenVectors(anmCalculator->getEigenvectors(), number_of_modes*mode_size, true);

	// Tantos pesos como modos calculemos (un peso por modo)
	//solver.setWeights(weights);

	// Atenuación
//	solver.setDistModificator(0.74);
	solver.setDistModificator(anmCalculator->getParameters()->getDisplacementFactor()*anmCalculator->getAlgorithm()->getInvBiggestNorm());
//	solver.setDistModificator(anmCalculator->getParameters()->getDisplacementFactor()/anmCalculator->getAlgorithm()->getBiggestNorm());
	cout<<"DIST MODIFICATOR  "<<solver.getDistModificator()<<endl;
	// Tantas distancias  como elementos tenga un modo (distancia en x,y,z del primer nodo,
	// del segundo etc

	double node_coord_displacements[mode_size];
	for(unsigned int i =0; i < new_points.size(); ++i){
		node_coord_displacements[i*3] = new_points[i].getX()-old_points[i].getX();
		node_coord_displacements[i*3+1] = new_points[i].getY()-old_points[i].getY();
		node_coord_displacements[i*3+2] = new_points[i].getZ()-old_points[i].getZ();
	}

	cout<<"Distances {";
	for (unsigned int i = 0; i < mode_size; ++i){
		cout<<node_coord_displacements[i]<<",";
	}
	cout<<"}";
	//exit(1);

	solver.setDistances(node_coord_displacements,mode_size);

	solver.solve();

	double* x = solver.getWeights();
	cout<<"Result: "<<endl;
	for(unsigned int i =0; i < c_alphas_size; ++i){
		cout<<x[i]<<" "<<endl;
	}
	cout<<endl;
	//---------------------------

	double e_result[] = {0.1506352313268,-0.02294251308032,	0.1829493671021};

	delete solvent;
	delete constraintParams;
	delete energyCalculator;
	delete anmMinParameters;
	delete anmMinimizer;
	delete anmParameters;
	delete anmCalculator;
	delete complex;


	return Assertion::assertExpectedVectorEqualsCalculatedVectorWithinPrecision(x,e_result,3,1e-5);
}


bool TestANMProteinRRT::test_expansion(){
		//------------------------------------
		// Load a 3-residue peptide of alanine
		//------------------------------------
		System system;
		ComplexBuilder complexBuilder;
		Complex * complex = complexBuilder.build("src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb");
		Solvent* solvent = SolventGenerator::createSolvent(*complex,false);

		// Get the number of CA
		vector<Atom*> c_alphas = complex->getAtomsWithName(AtomNames::CA);
		unsigned int c_alphas_size = c_alphas.size();

		// Backup old points
		vector<Point> old_points;
		for(unsigned int i =0; i < c_alphas.size();++i){
			old_points.push_back(c_alphas[i]->toPoint());
		}

		//-------------------------------------

		//------------------------------------------
		//Create the Minimizer and ANM Calculator
		//------------------------------------------
		PathPlanning::Tools::ANMObjectsPackage pack(&system, complex,solvent);
		pack.populateANMObjects("src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Data/anm_config.conf");
		//---------------------------

		//----------------------------
		// Doing the anm calculation step is mandatory (to compute the eigenvetors)
		//----------------------------
		// In this initial case, as the eigenvector computation and direction computation are coupled
		vector<double> final_weights;
		final_weights.push_back(0.8);
		final_weights.push_back(-0.45);
		final_weights.push_back(0.73);
		pack.anmCalculator->getParameters()->setWeights(final_weights);
		pack.anmCalculator->compute(pack.complex);

		//---------------------------
		// Create a solver
		//---------------------------
		Solver solver(pack.anmCalculator->getParameters()->getNumbermodes(), c_alphas_size*3);
		//solver.setDistModificator(0.74);
		//---------------------------


		//---------------------------
		// Create a boundaries object
		//---------------------------
		RangedBoundDescriptor rbd(-1,1,c_alphas_size*3);
		rbd.setBoundaries(NULL);
		//----------------------------

		//---------------------------
		// Create start and end nodes
		//---------------------------
		vector<double> initial_weights;
		initial_weights.push_back(0);
		initial_weights.push_back(0);
		initial_weights.push_back(0);

		ANMProteinConfiguration* initial_conf = new ANMProteinConfiguration(complex, pack.anmCalculator, &rbd, initial_weights);
		ANMProteinConfiguration* final_conf = 	new ANMProteinConfiguration(complex, pack.anmCalculator, &rbd,final_weights);

		//---------------------------

		//------------------------------------------
		//Create Node Expansor
		//------------------------------------------
		RRTNode initial_node;
		RRTNode objective_node;
		initial_node.setDataP(initial_conf);
		objective_node.setDataP(final_conf);

		ANMProteinRRTExpansionAlgorithm expansor(&pack,&solver);

		RRTNode* expanded = expansor.expand(&initial_node,&objective_node);

		ANMProteinConfiguration* expanded_conf = (ANMProteinConfiguration*)(expanded->getData());

		vector<double>& x =  expanded_conf->getWeights();
		for(unsigned int i =0; i < x.size();++i){
			cout<<x[i]<<endl;
		}
		//------------------------------------------

		// Compare configurations
		delete expanded;

		return true;
}


bool TestANMProteinRRT::test_sampling(){
	ANMProteinRRTSamplingAlgorithm sampler;
	sampler.setDimension(8);
	sampler.loadRandomNumbers("src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Data/random_numbers");

	System system;
	ComplexBuilder complexBuilder;
	Complex * complex = complexBuilder.build("src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb");

	vector<double> initial_weights;
	initial_weights.push_back(1);initial_weights.push_back(2);
	initial_weights.push_back(3);initial_weights.push_back(4);
	initial_weights.push_back(5);initial_weights.push_back(6);
	initial_weights.push_back(7);initial_weights.push_back(8);

	ANMProteinConfiguration* initial_conf = new ANMProteinConfiguration(complex, NULL, NULL, initial_weights);

	RRTNode initial;
	initial.setDataP(initial_conf);

	RRTNode* sample = sampler.sample(&initial);

	vector<double>& sampled_weights = static_cast<ANMProteinConfiguration*>(sample->getData())->getWeights();

	for(unsigned int i =0; i< sampled_weights.size(); i++){
		cout<<sampled_weights[i]<<endl;
	}

	return true;
}

bool TestANMProteinRRT::test_angular_weight_metric(){

	System system;
	ComplexBuilder complexBuilder;
	Complex * complex = complexBuilder.build("src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb");

	ProteinPathPlanning::ANMGuided::Metrics::AngularWeightMetric metric;

	// Create 'random' weights for the metrics

	vector<double> initial_weights;
	initial_weights.push_back(1);initial_weights.push_back(2);
	initial_weights.push_back(3);initial_weights.push_back(4);
	initial_weights.push_back(5);initial_weights.push_back(6);
	initial_weights.push_back(7);initial_weights.push_back(8);

	vector<double> final_weights;
	final_weights.push_back(4);final_weights.push_back(8);
	final_weights.push_back(3);final_weights.push_back(7);
	final_weights.push_back(2);final_weights.push_back(6);
	final_weights.push_back(1);final_weights.push_back(5);

	ANMProteinConfiguration* first_conf = new ANMProteinConfiguration(complex, NULL, NULL, initial_weights);
	ANMProteinConfiguration* second_conf = 	new ANMProteinConfiguration(complex, NULL, NULL,final_weights);

	RRTNode first; first.setDataP(first_conf);
	RRTNode second; second.setDataP(second_conf);

	return Assertion::assertExpectedEqualsCalculatedWithinPrecision(metric.calcDistance(&first,&second),0.735294117647,1e-4);
}


bool TestANMProteinRRT::test_cartesian_weight_metric(){
	System system;
	ComplexBuilder complexBuilder;
	Complex * complex = complexBuilder.build("src/Molecules/Test/Data/ProteinResiduesSamples/plop_ala.pdb");

	ProteinPathPlanning::ANMGuided::Metrics::CartesianWeightMetric metric;

	// Create 'random' weights for the metrics

	vector<double> initial_weights;
	initial_weights.push_back(1);initial_weights.push_back(2);
	initial_weights.push_back(3);initial_weights.push_back(4);
	initial_weights.push_back(5);initial_weights.push_back(6);
	initial_weights.push_back(7);initial_weights.push_back(8);

	vector<double> final_weights;
	final_weights.push_back(4);final_weights.push_back(8);
	final_weights.push_back(3);final_weights.push_back(7);
	final_weights.push_back(2);final_weights.push_back(6);
	final_weights.push_back(1);final_weights.push_back(5);

	ANMProteinConfiguration* first_conf = new ANMProteinConfiguration(complex, NULL, NULL, initial_weights);
	ANMProteinConfiguration* second_conf = 	new ANMProteinConfiguration(complex, NULL, NULL,final_weights);

	RRTNode first; first.setDataP(first_conf);
	RRTNode second; second.setDataP(second_conf);

	return Assertion::assertExpectedEqualsCalculatedWithinPrecision(metric.calcDistance(&first,&second),10.3923,1e-4);
}

/* -----------------------------------------------------------
Function: void TestANMProteinRRT::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestANMProteinRRT::run(){
	Test::run();

	//----------------------------------------------------
	//TEST_FUNCTION(test_rrt_build)
	TEST_FUNCTION(test_solve_weights)
	//TEST_FUNCTION(test_expansion)
	//TEST_FUNCTION(test_sampling)
	//TEST_FUNCTION(test_angular_weight_metric)
	//TEST_FUNCTION(test_cartesian_weight_metric)
	//-----------------------------------------------------

	finish();
}

/* -----------------------------------------------------------
Function: void TestANMProteinRRT::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestANMProteinRRT::finish(){

	//-----------------------------------------------------

	//-----------------------------------------------------
	Test::finish();
}


