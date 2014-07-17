/*
 * ANMG2DStartNodePicker.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "ANMG2DStartNodePicker.h"

ANMG2DStartNodePicker::ANMG2DStartNodePicker(RRTMetric* m):StartNodePicker(m) {

}

ANMG2DStartNodePicker::~ANMG2DStartNodePicker() {
}

RRTNode *ANMG2DStartNodePicker::pick_new_starting_node(vector<RRTNode*> & nodes){
	// In the 2D case we just pick the node which is closer to the goal node.
	// This does not mean we are going to get it faster though...
	// This is exactly (line by line) the same function used in the
	// 2D RRT for nearest neighbour brute force search.

	double min_distance = std::numeric_limits<double>::max();
	RRTNode* min_dist_node = NULL;

	for(unsigned int i = 0; i < nodes.size();i++){
		double dist = metric->calcDistance(nodes[i],getGoal());
		if( dist < min_distance){
			min_dist_node = nodes[i];
			min_distance = dist;
		}
	}

	return min_dist_node;
}



