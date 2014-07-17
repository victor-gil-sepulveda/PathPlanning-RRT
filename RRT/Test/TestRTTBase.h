/*
 * TestRTTBase.h
 *
 *  Created on: Jun 1, 2011
 *      Author: vgil
 */

#ifndef TESTRTTBASE_H_
#define TESTRTTBASE_H_

#include "../../../Tools/TestTools.h"
#include "../RRTGlobal.h"

class TestRTTBase : public Test{

	public:

		TestRTTBase();

		TestRTTBase(string name);

		virtual ~TestRTTBase();

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

		bool test_timer();
		bool test_timer_recursive();

		//---------------------------

};



#endif /* TESTRTTBASE_H_ */
