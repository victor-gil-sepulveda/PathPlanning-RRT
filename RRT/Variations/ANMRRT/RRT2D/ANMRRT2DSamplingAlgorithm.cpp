/*
 * ANMRRT2DSamplingAlgorithm.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#include "ANMRRT2DSamplingAlgorithm.h"

ANMRRT2DSamplingAlgorithm::ANMRRT2DSamplingAlgorithm(bool save_random):RRT2DSamplingAlgorithm(save_random){
	srand ( time(NULL) );
}

ANMRRT2DSamplingAlgorithm::~ANMRRT2DSamplingAlgorithm() {

}

int	ANMRRT2DSamplingAlgorithm::gen_random (){
	return rand();
}

RRTNode *ANMRRT2DSamplingAlgorithm::do_sample(RRTNode *initial, vector<int>& rand_num){

	// Generate new configuration
	ANMRRT2DConfiguration* rand_conf = new ANMRRT2DConfiguration;


	// Normalize random_numbers between [-1,1]
	vector<double> norm_rand;
	int maxrand = *(std::max_element(rand_num.begin(),rand_num.end()));

	// Divide all numbers by maxrand/2. to have them in the range [0,2]
	// and substract 1 to have them in the range [-1,1]
	for(unsigned int i = 0; i<rand_num.size();++i){
			norm_rand.push_back(((double)(rand_num[i])/(maxrand/2))-1.);
	}

	rand_conf->setAmplitudes(norm_rand);

	// Then we sample the values for x and y
	rand_conf->setX(rand_num[0] % getCollisionMapW());
	rand_conf->setY(rand_num[1] % getCollisionMapH());

	// Create new node
	RRTNode* node = new RRTNode;
	node->setDataP(dynamic_cast<RRTConfiguration*>(rand_conf));


	return node;
}
