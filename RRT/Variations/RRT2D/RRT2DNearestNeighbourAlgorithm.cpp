/*
 * RRT2DNearestNeighbourAlgorithm.cpp
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#include "RRT2DNearestNeighbourAlgorithm.h"

RRT2DNearestNeighbourAlgorithm::RRT2DNearestNeighbourAlgorithm(RRT2DMetric* m):NearestNeighbourAlgorithm(dynamic_cast<RRTMetric*>(m)) {
}

RRT2DNearestNeighbourAlgorithm::~RRT2DNearestNeighbourAlgorithm(){
}


RRTNode* RRT2DNearestNeighbourAlgorithm::get_nearest_neighbour(vector<RRTNode*>& target_nodes, RRTNode* node){

	// Brute force version
	double min_distance = std::numeric_limits<double>::max();
	RRTNode* min_dist_node = NULL;

	for(unsigned int i = 0; i < target_nodes.size();i++){
		double dist = getMetric()->calcDistance(target_nodes[i],node);
		if( dist < min_distance){
			min_dist_node = target_nodes[i];
			min_distance = dist;
		}
	}

	return min_dist_node;
}
