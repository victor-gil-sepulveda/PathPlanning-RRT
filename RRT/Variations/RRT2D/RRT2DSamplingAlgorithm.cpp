/*
 * RRT2DSamplingAlgorithm.cpp
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#include "RRT2DSamplingAlgorithm.h"

RRT2DSamplingAlgorithm::RRT2DSamplingAlgorithm(bool save_random): SamplingAlgorithm(save_random){
	// Seed rand function
	seed = time(NULL);
	srand ( seed );
}

RRT2DSamplingAlgorithm::~RRT2DSamplingAlgorithm(){
}

int	RRT2DSamplingAlgorithm::gen_random (){
	return rand();
}


RRTNode *RRT2DSamplingAlgorithm::do_sample(RRTNode *initial, vector<int>& rand_num){

	// Generate new configuration
	RRT2DConfiguration* rand_conf = new RRT2DConfiguration;
	rand_conf->setX(rand_num[0] % getCollisionMapW());
	rand_conf->setY(rand_num[1] % getCollisionMapH());

	// Create new node
	RRTNode* node = new RRTNode;
	node->setDataP(dynamic_cast<RRTConfiguration*>(rand_conf));

	return node;
}

unsigned int RRT2DSamplingAlgorithm::getCollisionMapH() const
{
    return collision_map_h;
}

unsigned int RRT2DSamplingAlgorithm::getCollisionMapW() const
{
    return collision_map_w;
}

void RRT2DSamplingAlgorithm::setCollisionMapH(unsigned int collision_map_h)
{
    this->collision_map_h = collision_map_h;
}

void RRT2DSamplingAlgorithm::setCollisionMapW(unsigned int collision_map_w)
{
    this->collision_map_w = collision_map_w;
}







