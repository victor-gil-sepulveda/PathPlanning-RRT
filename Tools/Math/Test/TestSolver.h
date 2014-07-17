/*
 * TestSolver.h
 *
 *  Created on: 30/06/2011
 *      Author: victor
 */

#ifndef TestSolver_H_
#define TestSolver_H_

#include "../../../../Tools/TestTools.h"
#include "../Solver.h"

class TestSolver : public Test{

	public:

		TestSolver();

		TestSolver(string name);

		virtual ~TestSolver();

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
		bool test_solver();
		bool test_minimath_solving_scenario();
		bool test_solve_projections();
		//---------------------------

};

#endif
