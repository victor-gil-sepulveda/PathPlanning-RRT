/*
 * RRT2DColisionTest.h
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#ifndef RRT2DCOLISIONTEST_H_
#define RRT2DCOLISIONTEST_H_

#include <cstdio>
#include <string>
using namespace std;

#include "RRT2DConfiguration.h"
#include "RRT2DMetric.h"
#include "../../BaseAlgorithms/ColisionTest.h"


class RRT2DColisionTest: public ColisionTest {
		public:
								RRT2DColisionTest	(RRT2DMetric* m);
			virtual 			~RRT2DColisionTest	();

			bool				setCollisionMap		(const char* fieldPath);
			unsigned char*		getCollisionMap		();
			unsigned int 		getCollisionMapH	() const;
			unsigned int 		getCollisionMapW	() const;
			void 				setCollisionMapH	(unsigned int collision_map_h);
			void 				setCollisionMapW	(unsigned int collision_map_w);

		private:
			bool 				test_collision		(RRTNode* node);
			unsigned char*		collision_map;
			unsigned int 		collision_map_w;
			unsigned int 		collision_map_h;
};

#endif /* RRT2DCOLISIONTEST_H_ */
