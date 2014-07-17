/*
 * ANMG2DStartNodePicker.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef ANMG2DSTARTNODEPICKER_H_
#define ANMG2DSTARTNODEPICKER_H_

#include <limits>
using namespace std;

#include "../../Basealgorithms/StartNodePicker.h"

class ANMG2DStartNodePicker: public StartNodePicker {
		public:
			ANMG2DStartNodePicker(RRTMetric* m);
			virtual ~ANMG2DStartNodePicker();

		private:
			virtual RRTNode*	pick_new_starting_node 	(vector<RRTNode*>& nodes);
};

#endif /* ANMG2DSTARTNODEPICKER_H_ */
