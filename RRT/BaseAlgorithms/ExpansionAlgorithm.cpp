/*
 * ExpansionAlgorithm.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "ExpansionAlgorithm.h"

ExpansionAlgorithm::ExpansionAlgorithm(RRTMetric* m): metric(m) {

}

ExpansionAlgorithm::~ExpansionAlgorithm() {
}

RRTNode* ExpansionAlgorithm::expand(RRTNode *from, RRTNode *to){
	return do_expansion(from, to);
}

RRTMetric *ExpansionAlgorithm::getMetric() const
{
    return metric;
}

void ExpansionAlgorithm::setMetric(RRTMetric *metric)
{
    this->metric = metric;
}




