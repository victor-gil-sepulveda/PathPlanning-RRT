/*
 * RRT2DMetric.cpp
 *
 *  Created on: May 26, 2011
 *      Author: vgil
 */

#include "RRT2DMetric.h"

RRT2DMetric::RRT2DMetric(){

}

RRT2DMetric::~RRT2DMetric(){
}

double RRT2DMetric::calc_distance(RRTNode *first, RRTNode *second){
	RRT2DConfiguration* c1 = dynamic_cast<RRT2DConfiguration*>(first->getData());
	RRT2DConfiguration* c2 = dynamic_cast<RRT2DConfiguration*>(second->getData());
	return sqrt(pow(c1->getX()-c2->getX(),2)+pow(c1->getY()-c2->getY(),2));
}


