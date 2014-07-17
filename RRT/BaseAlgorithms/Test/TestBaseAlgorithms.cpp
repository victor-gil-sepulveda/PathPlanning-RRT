#include "TestBaseAlgorithms.h"

/*-----------------------------------------------------------
Function: TestBaseAlgorithms::TestBaseAlgorithms()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestBaseAlgorithms::TestBaseAlgorithms(){
	Test::create("");
}

/* -----------------------------------------------------------
Function: TestBaseAlgorithms::TestBaseAlgorithms(string name)

Description:
Initializes the test class giving it a name.

In:
void

Out:
void
-----------------------------------------------------------------*/

TestBaseAlgorithms::TestBaseAlgorithms(string name){
	Test::create(name);
}

/*-----------------------------------------------------------
Function: TestBaseAlgorithms:~TestBaseAlgorithms()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestBaseAlgorithms::~TestBaseAlgorithms(){

}

/*-----------------------------------------------------------
Function:void TestBaseAlgorithms::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestBaseAlgorithms::init(){

	// Initialize vars we are going to use globally


}

bool TestBaseAlgorithms::test_serialization(){
	vector<RRTNode*> dummyvector;

	DummyRRTSerializationAlgorithm serAlg;
	serAlg.setBaseFile(string("MyFile"));
	serAlg.setBasePath(string("Basepath"));

	serAlg.setMaxFiles(1000);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	string s1 =serAlg.getSavedFile();

	serAlg.setMaxFiles(10);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	string s2 =serAlg.getSavedFile();

	serAlg.setMaxFiles(0);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	string s3 =serAlg.getSavedFile();

	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	serAlg.saveState(dummyvector);
	string s4 =serAlg.getSavedFile();

	serAlg.setFileType(string("txt"));
	serAlg.saveState(dummyvector);
	string s5 =serAlg.getSavedFile();

	return 	s1 == string("Basepath/MyFile0001") &&
			s2 == string("Basepath/MyFile03") &&
			s3 == string("Basepath/MyFile5") &&
			s4 == string("Basepath/MyFile10") &&
			s5 == string("Basepath/MyFile11.txt") ;
}


// Just to test if the base algorithm is storing things ok.

bool TestBaseAlgorithms::test_sampling(){
	DummySamplingAlgorithm samp;
	RRTNode dummyinitial;
	samp.setDimension(2);

	// First do 100 samples
	vector<int> data;
	for(unsigned int i =0;i<100;i++){
		samp.sample(&dummyinitial);
		data.push_back(i*2);
		data.push_back(i*2+1);
	}

	vector<int>& random_numbers = samp.getRandomNumbers();
	if(data.size()!= random_numbers.size()){
		return false;
	}

	// Now compare the stored numbers
	for(unsigned int i =0;i<data.size();i++){
		if (random_numbers[i] != data[i]){
			return false;
		}
	}

	return true;
}

bool TestBaseAlgorithms::test_sampling_save(){
	DummySamplingAlgorithm samp;
	RRTNode dummyinitial;
	samp.setDimension(2);

	// Do 10 samples (will generate numbers from 0 to 19)
	vector<int> data;
	for(unsigned int i =0;i<10;i++){
		samp.sample(&dummyinitial);
		data.push_back(i*2);
		data.push_back(i*2+1);
	}

	// Now save this numbers
	samp.saveRandomNumbers(string("src/PathPlanning/RRT/BaseAlgorithms/Test/Tmp/test_random"));

	// Compare it with golden data
	bool test1 =  TestTools::exec("diff src/PathPlanning/RRT/BaseAlgorithms/Test/Tmp/test_random src/PathPlanning/RRT/BaseAlgorithms/Test/Data/random_1") == string("");

	if(!test1) cout<<"Generated numbers were different."<<endl;

	// Now we generate other series
	vector<int> new_series;
	for(unsigned int i =0; i < samp.getRandomNumbers().size(); i++){
		new_series.push_back(i*10);
	}

	// Load golden data into the sampler
	samp.loadRandomNumbers(string("src/PathPlanning/RRT/BaseAlgorithms/Test/Data/random_2"));

	// Compare the pregenrated vector with the new loaded one
	bool test2 = isTheSame(samp.getRandomNumbers(),new_series);
	if(!test2) cout<<"Load failed."<<endl;


	// Ok, and finally we try to load a file and then check if we are using this to sample
	vector<int>& sampled = samp.getSampled();
	samp.reset();
	for(int i = 0;i<10; i++){
		samp.sample(&dummyinitial);
	}

	int random_3[] ={1,2,3,2,5,9,2,56,6,25,62,25,14,14,65,78,5,878,9,54};

	samp.reset();
	samp.loadRandomNumbers(string("src/PathPlanning/RRT/BaseAlgorithms/Test/Data/random_3"));

	bool test3 = true;
	for(unsigned int i =0; i < sampled.size(); i++){
		if(sampled[i]!=random_3[i]){
			test3=false;
			cout<<"Diferences at "<<i<<": sampled is "<<sampled[i]<<" expected was "<<random_3[i]<<endl;
		}
	}

	return test1 && test2 && test3;

}

/* -----------------------------------------------------------
Function: void TestBaseAlgorithms::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestBaseAlgorithms::run(){
	Test::run();
	//----------------------------------------------------

	TEST_FUNCTION(test_serialization)
	TEST_FUNCTION(test_sampling)
	TEST_FUNCTION(test_sampling_save)

	//-----------------------------------------------------
	finish();
}

/* -----------------------------------------------------------
Function: void TestBaseAlgorithms::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestBaseAlgorithms::finish(){

	//-----------------------------------------------------

	//-----------------------------------------------------
	Test::finish();
}


