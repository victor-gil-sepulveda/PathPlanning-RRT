/*
 * ANMRRT2DSamplingAlgorithm.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef ANMRRT2DSAMPLINGALGORITHM_H_
#define ANMRRT2DSAMPLINGALGORITHM_H_

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <algorithm>
using namespace std;

#include "../../../Variations/RRT2D/RRT2DSamplingAlgorithm.h"
#include "ANMRRT2DConfiguration.h"

class ANMRRT2DSamplingAlgorithm: public RRT2DSamplingAlgorithm {

	public:

						ANMRRT2DSamplingAlgorithm		(bool save_random = false);
		virtual 		~ANMRRT2DSamplingAlgorithm		();

	private:

		virtual 		int				gen_random		();
		virtual 		RRTNode*		do_sample		(RRTNode* initial, vector<int>& rand_num);


};

#endif /* ANMRRT2DSAMPLINGALGORITHM_H_ */
