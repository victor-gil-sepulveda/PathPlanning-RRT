/*
 * RRT2DSamplingAlgorithm.h
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#ifndef RRT2DSAMPLINGALGORITHM_H_
#define RRT2DSAMPLINGALGORITHM_H_

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <limits>
using namespace std;

#include "RRT2DConfiguration.h"
#include "../../BaseAlgorithms/SamplingAlgorithm.h"

class RRT2DSamplingAlgorithm: public SamplingAlgorithm{

		public:
							RRT2DSamplingAlgorithm		(bool save_random = false);
			virtual 		~RRT2DSamplingAlgorithm		();

			unsigned int 	getCollisionMapH			() const;
			unsigned int 	getCollisionMapW			() const;

			void 			setCollisionMapH			(unsigned int collision_map_h);
			void 			setCollisionMapW			(unsigned int collision_map_w);

		private:
			virtual int 	gen_random					();
			virtual RRTNode*do_sample					(RRTNode* initial,vector<int>& rand_num);

			unsigned int 	collision_map_w;
			unsigned int 	collision_map_h;
			unsigned int 	seed;
};

#endif /* RRT2DSAMPLINGALGORITHM_H_ */
