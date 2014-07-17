/*
 * RRT2DMetric.h
 *
 *  Created on: May 26, 2011
 *      Author: vgil
 */

#ifndef RRT2DMETRIC_H_
#define RRT2DMETRIC_H_

#include "../../BaseAlgorithms/RRTMetric.h"
#include "RRT2DConfiguration.h"


class RRT2DMetric: public RRTMetric {
		public:
									RRT2DMetric		();
						virtual 	~RRT2DMetric	();

		private:
			virtual 	double 		calc_distance	(RRTNode* first, RRTNode* second);
};

#endif /* RRT2DMETRIC_H_ */
