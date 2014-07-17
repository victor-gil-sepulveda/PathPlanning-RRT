/*
Files: TestASA_CG.h TestASA_CG.cpp

Started: 04/08/10

Description: Test Class for Atom Class testing.

*/

#ifndef TestASA_CG_H_
#define TestASA_CG_H_

#include <string>
#include "../../../../../Tools/TestTools.h"
#include "../../../../../Tools/Math/MathTools.h"
#include "../../MatrixOps.h"
#include "../asa_user.h"
#include "../asa_cg.h"

class TestASA_CG : public Test{

	public:

		TestASA_CG();

		TestASA_CG(string name);

		virtual ~TestASA_CG();

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
		bool test_solving();
		bool test_minimath_1();
		bool test_minimath_2();
		bool test_minimath_3();
		bool test_minimath_4();
		//---------------------------

};

#endif /* TestASA_CG_H_ */
