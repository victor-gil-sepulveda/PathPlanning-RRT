/*
 * RRTMetric.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "RRTMetric.h"

RRTMetric::RRTMetric(){
	setTolerance(0);
}

RRTMetric::~RRTMetric(){
}

double RRTMetric::calcDistance(RRTNode *first, RRTNode *second){
	return calc_distance(first,second);
}

bool RRTMetric::closeTo(RRTNode *first, RRTNode *second){
	return calcDistance(first,second) <= tolerance;
}

bool RRTMetric::overlaps(RRTNode *first, RRTNode *second){
	return calcDistance(first,second) == 0;
}

double RRTMetric::getTolerance(){
	return tolerance;
}

void RRTMetric::setTolerance(double tol){
	this->tolerance = tol;
}






