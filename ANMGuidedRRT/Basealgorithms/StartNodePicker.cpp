/*
 * StartNodePicker.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "StartNodePicker.h"

StartNodePicker::StartNodePicker(RRTMetric* m) {
	setMetric(m);
}

StartNodePicker::~StartNodePicker() {
}

RRTNode *StartNodePicker::pickNewStartingNode(vector<RRTNode*> & nodes){
	return pick_new_starting_node(nodes);
}

RRTMetric *StartNodePicker::getMetric() const
{
    return metric;
}

RRTNode* StartNodePicker::getGoal() const
{
	return this->goal;
}

void StartNodePicker::setMetric(RRTMetric *metric){
    this->metric = metric;
}


void StartNodePicker::setGoal(RRTNode* node){
	this->goal = node;
}

