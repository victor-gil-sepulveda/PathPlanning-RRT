/*
 * NearestNeighbourAlgorithm.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "NearestNeighbourAlgorithm.h"

NearestNeighbourAlgorithm::NearestNeighbourAlgorithm(RRTMetric* m):metric(m){
}

NearestNeighbourAlgorithm::~NearestNeighbourAlgorithm() {
}

RRTNode* NearestNeighbourAlgorithm::getNearestNeighbour(vector<RRTNode*>& target_nodes, RRTNode *node){
	return get_nearest_neighbour(target_nodes,node);
}

RRTMetric *NearestNeighbourAlgorithm::getMetric() const
{
    return metric;
}

void NearestNeighbourAlgorithm::setMetric(RRTMetric *metric)
{
    this->metric = metric;
}




