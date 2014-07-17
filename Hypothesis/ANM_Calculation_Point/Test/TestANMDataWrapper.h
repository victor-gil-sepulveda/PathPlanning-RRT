/*
 * TestANMDataWrapper.h
 *
 *  Created on: Jun 1, 2011
 *      Author: vgil
 */

#ifndef TestANMDataWrapper_H_
#define TestANMDataWrapper_H_

#include "../../../../Tools/TestTools.h"
#include "../ANMDataWrapper.h"

class TestANMDataWrapper : public Test{

	public:

		TestANMDataWrapper();

		TestANMDataWrapper(string name);

		virtual ~TestANMDataWrapper();

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

		bool test_calculate_projections();
		bool test_smart_calculate_projections();
		bool test_weight_solving();
		//---------------------------



};



#endif /* TestANMDataWrapper_H_ */
