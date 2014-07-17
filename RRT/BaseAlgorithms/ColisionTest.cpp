/*
 * ColisionTest.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "ColisionTest.h"

ColisionTest::ColisionTest(RRTMetric* m) : metric(m){
}

ColisionTest::~ColisionTest() {
}

bool ColisionTest::testCollision(RRTNode *node){
	return test_collision(node);
}

RRTMetric *ColisionTest::getMetric() const
{
    return metric;
}

void ColisionTest::setMetric(RRTMetric *metric)
{
    this->metric = metric;
}




