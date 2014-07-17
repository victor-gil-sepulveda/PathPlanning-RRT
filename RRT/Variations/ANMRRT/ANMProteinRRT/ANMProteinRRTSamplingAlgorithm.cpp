/*
 * ANMProteinRRTSamplingAlgorithm.cpp
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#include "ANMProteinRRTSamplingAlgorithm.h"


ANMProteinRRTSamplingAlgorithm::ANMProteinRRTSamplingAlgorithm(bool save_random):SamplingAlgorithm(save_random) {
	srand(time(NULL));
}

ANMProteinRRTSamplingAlgorithm::~ANMProteinRRTSamplingAlgorithm() {
}


int	ANMProteinRRTSamplingAlgorithm::gen_random (){
	return rand();
}

RRTNode* ANMProteinRRTSamplingAlgorithm::do_sample (RRTNode* initial, vector<int>& rand_num){

	// Genera pesos entre -1 y 1
	vector<double> weights(rand_num.size(),0.);

	// Put all numbers between 0 and 1

	for(unsigned int i =0; i < weights.size(); ++i){
		weights[i] = ((double)(2*rand_num[i])) / RAND_MAX;
	}

	double maxn = *(std::max_element(weights.begin(),weights.end()));
	double minn = *(std::min_element(weights.begin(),weights.end()));
	double mid_range = (maxn - minn) / 2.;

	for(unsigned int i =0; i < weights.size(); ++i){
		// Center the number and normalize it between 1 and -1
		weights[i] = weights[i]-mid_range;
	}

	// A new sampled configuration only needs the sampled weights
	ANMProteinConfiguration* sample_conf = new ANMProteinConfiguration(static_cast<ANMProteinConfiguration*>(initial->getData())->getProtein(),NULL,NULL,weights);

	RRTNode* sample= new RRTNode;
	sample->setDataP(sample_conf);

	return sample;
}
