/*
 * RRT2DExpansionAlgorithm.cpp
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#include "RRT2DExpansionAlgorithm.h"

RRT2DExpansionAlgorithm::RRT2DExpansionAlgorithm(RRT2DMetric* m) : ExpansionAlgorithm(dynamic_cast<RRTMetric*>(m)) {
	setExpansionDistance(0);
	setCollisionMapH(0);
	setCollisionMapW(0);
}

RRT2DExpansionAlgorithm::~RRT2DExpansionAlgorithm() {
}

RRTNode *RRT2DExpansionAlgorithm::do_expansion(RRTNode *from, RRTNode *to){

	RRT2DConfiguration* c_from = dynamic_cast<RRT2DConfiguration*>(from->getData());
	RRT2DConfiguration* c_to = dynamic_cast<RRT2DConfiguration*>(to->getData());
	RRT2DConfiguration* c_expand = new RRT2DConfiguration;

	double dist = getMetric()->calcDistance(from,to);
	if(dist > 0.5){
		double unit_vector_x = (c_to->getX() - c_from->getX())/dist;
		double unit_vector_y = (c_to->getY() - c_from->getY())/dist;

		int coord = (int)(unit_vector_x * getExpansionDistance()+c_from->getX());
		if (coord > (int)getCollisionMapW()) coord = getCollisionMapW();
		if (coord < 0) coord = 0;
		c_expand->setX(coord);

		coord = (int)(unit_vector_y * getExpansionDistance()+c_from->getY());
		if (coord > (int)getCollisionMapH()) coord = getCollisionMapH();
		if (coord < 0) coord = 0;
		c_expand->setY(coord);

		RRTNode* expanded = new RRTNode;
		expanded->setDataP(c_expand);

		return expanded;
	}
	else{
		delete c_expand;
		return NULL;
	}
}

unsigned int RRT2DExpansionAlgorithm::getExpansionDistance() const
{
    return expansion_distance;
}

void RRT2DExpansionAlgorithm::setExpansionDistance(unsigned int expansion_distance)
{
    this->expansion_distance = expansion_distance;
}



unsigned int RRT2DExpansionAlgorithm::getCollisionMapH	() const{
	return collision_map_h;
}

unsigned int RRT2DExpansionAlgorithm::getCollisionMapW	() const{
	return collision_map_w;
}

void RRT2DExpansionAlgorithm::setCollisionMapH	(unsigned int collision_map_h){
	this->collision_map_h = collision_map_h;
}

void RRT2DExpansionAlgorithm::setCollisionMapW	(unsigned int collision_map_w){
	this->collision_map_w = collision_map_w;
}
