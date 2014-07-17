/*
 * ANMProteinRRTMetric.cpp
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#include "AngularWeightMetric.h"


#define AngularWeightMetricPackage ProteinPathPlanning::ANMGuided::Metrics::AngularWeightMetric

AngularWeightMetricPackage::AngularWeightMetric():RRTMetric(){}

AngularWeightMetricPackage::~AngularWeightMetric(){}

double	AngularWeightMetricPackage::calc_distance (RRTNode* first, RRTNode* second){
	ANMProteinConfiguration* first_conf = dynamic_cast<ANMProteinConfiguration*>(first->getData());
	ANMProteinConfiguration* second_conf = dynamic_cast<ANMProteinConfiguration*>(second->getData());

	double first_norm = Math::ourDnrm2(first_conf->getWeights().size(),&(first_conf->getWeights())[0]);
	double second_norm = Math::ourDnrm2(second_conf->getWeights().size(),&(second_conf->getWeights())[0]);
	double dot = Math::dotProduct(first_conf->getWeights().size(),&(first_conf->getWeights())[0],
						&(second_conf->getWeights())[0]);

	return dot / (first_norm*second_norm);
}

#undef AngularWeightMetricPackage
