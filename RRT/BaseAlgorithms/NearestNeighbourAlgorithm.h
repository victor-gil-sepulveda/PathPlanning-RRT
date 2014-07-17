/*
 * NearestNeighbourAlgorithm.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef NEARESTNEIGHBOURALGORITHM_H_
#define NEARESTNEIGHBOURALGORITHM_H_

#include "RRTBaseAlgorithm.h"
#include "RRTMetric.h"

class NearestNeighbourAlgorithm: public RRTBaseAlgorithm {
		public:
								NearestNeighbourAlgorithm		(RRTMetric* m = NULL);
			virtual 			~NearestNeighbourAlgorithm		();

			RRTNode* 			getNearestNeighbour				(vector<RRTNode*>& target_nodes, RRTNode* node);
			RRTMetric *			getMetric						() const;
			void 				setMetric						(RRTMetric *metric);

		protected:
			virtual RRTNode* 	get_nearest_neighbour			(vector<RRTNode*>& target_nodes, RRTNode* node) =0;
			RRTMetric* 			metric;
};

#endif /* NEARESTNEIGHBOURALGORITHM_H_ */
