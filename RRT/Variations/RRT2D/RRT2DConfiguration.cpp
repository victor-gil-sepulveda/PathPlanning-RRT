/*
 * RRT2DConfiguration.cpp
 *
 *  Created on: May 26, 2011
 *      Author: vgil
 */

#include "RRT2DConfiguration.h"

RRT2DConfiguration::RRT2DConfiguration() {
	setX(0);
	setY(0);
}

RRT2DConfiguration::~RRT2DConfiguration() {
}

int RRT2DConfiguration::getX() const
{
    return x;
}

int RRT2DConfiguration::getY() const
{
    return y;
}

void RRT2DConfiguration::setX(int x)
{
    this->x = x;
}

void RRT2DConfiguration::setY(int y)
{
    this->y = y;
}


string 	RRT2DConfiguration::toString() const{
	ostringstream s;
	s << string("[ ")<<getX()<<string(",")<<getY()<<string(" ]");
	return s.str();
}
