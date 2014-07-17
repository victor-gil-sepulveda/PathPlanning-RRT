/*
 * RRT2DNearestNeighbourAlgorithm.h
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#ifndef RRT2DNEARESTNEIGHBOURALGORITHM_H_
#define RRT2DNEARESTNEIGHBOURALGORITHM_H_

#include <limits>
using namespace std;

#include "../../BaseAlgorithms/NearestNeighbourAlgorithm.h"
#include "RRT2DMetric.h"

class RRT2DNearestNeighbourAlgorithm: public NearestNeighbourAlgorithm {

	public:
						RRT2DNearestNeighbourAlgorithm		(RRT2DMetric* m);
		virtual 		~RRT2DNearestNeighbourAlgorithm		();

	private:
		RRTNode* 		get_nearest_neighbour				(vector<RRTNode*>& target_nodes, RRTNode* node);

};

#endif /* RRT2DNEARESTNEIGHBOURALGORITHM_H_ */
