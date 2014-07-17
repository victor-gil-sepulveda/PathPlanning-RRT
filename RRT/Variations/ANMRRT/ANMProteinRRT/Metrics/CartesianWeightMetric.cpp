/*
 * ANMProteinRRTMetric.cpp
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#include "CartesianWeightMetric.h"

#define CartesianWeightMetricPackage ProteinPathPlanning::ANMGuided::Metrics::CartesianWeightMetric

CartesianWeightMetricPackage::CartesianWeightMetric():RRTMetric(){}

CartesianWeightMetricPackage::~CartesianWeightMetric(){}

double	CartesianWeightMetricPackage::calc_distance (RRTNode* first, RRTNode* second){
	ANMProteinConfiguration* first_conf = dynamic_cast<ANMProteinConfiguration*>(first->getData());
	ANMProteinConfiguration* second_conf = dynamic_cast<ANMProteinConfiguration*>(second->getData());

	vector<double>& first_weights = first_conf->getWeights();
	vector<double>& second_weights = second_conf->getWeights();

	double dist2 = 0;

	for (unsigned int i = 0; i < first_weights.size(); ++i) {
		dist2 +=  (first_weights[i]-second_weights[i])*(first_weights[i]-second_weights[i]);
	}

	return sqrt(dist2);
}

#undef CartesianWeightMetricPackage
