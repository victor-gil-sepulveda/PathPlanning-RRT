/*
Files: TestBaseAlgorithms.h TestBaseAlgorithms.cpp

Started: 21/09/10

Description: Test Suite for PDBReader and PDBWriter classes.

*/

#ifndef TestBaseAlgorithms_H_
#define TestBaseAlgorithms_H_



#include "../../../../Tools/TestTools.h"
#include "DummyRRTSerializationAlgorithm.h"
#include "DummySamplingAlgorithm.h"

class TestBaseAlgorithms : public Test{

	public:

		TestBaseAlgorithms();

		TestBaseAlgorithms(string name);

		virtual ~TestBaseAlgorithms();

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

		bool test_serialization();
		bool test_sampling();
		bool test_sampling_save();

		//---------------------------

};

#endif
