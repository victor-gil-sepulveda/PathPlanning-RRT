/*
 * RRT2DColisionTest.cpp
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#include "RRT2DColisionTest.h"

RRT2DColisionTest::RRT2DColisionTest(RRT2DMetric* m):
								ColisionTest(dynamic_cast<RRTMetric*>(m)),
								collision_map(NULL),
								collision_map_w(0),
								collision_map_h(0)

{}

RRT2DColisionTest::~RRT2DColisionTest(){
	if(collision_map) free(collision_map);
}

bool RRT2DColisionTest::setCollisionMap	(const char* fieldPath){

	// Open file
	FILE* f = fopen(fieldPath,"rb");
	if (!f) {
		cout<<"[RTT2D setCollisionMap] Error, fichero no encontrado: "<<string(fieldPath)<<endl;
		return false;
	}

	// Read dimensions
	fread(&collision_map_w,sizeof(int),1,f);
	fread(&collision_map_h,sizeof(int),1,f);
	cout<<"Loaded scenario  of dimensions: "<<collision_map_w<<" X "<<collision_map_h<<". "<<flush<<endl;

	// Read data
	collision_map = (unsigned char*) malloc(collision_map_h*collision_map_w*sizeof(unsigned char));
	unsigned int bytesread = fread(getCollisionMap(),sizeof(unsigned char),collision_map_h*collision_map_w*sizeof(unsigned char),f);
	cout<< bytesread <<" bytes read out of "<< collision_map_h*collision_map_w*sizeof(unsigned char)<<". "<<endl;
	fclose(f);

	return true;
}

unsigned char* RRT2DColisionTest::getCollisionMap(){
	return collision_map;
}

bool RRT2DColisionTest::test_collision(RRTNode *node){
	RRT2DConfiguration* c = dynamic_cast<RRT2DConfiguration*>(node->getData());
	return (unsigned int) getCollisionMap()[c->getX()+c->getY()*collision_map_w] != (unsigned int) 255;
}

unsigned int RRT2DColisionTest::getCollisionMapH() const
{
    return collision_map_h;
}

unsigned int RRT2DColisionTest::getCollisionMapW() const
{
    return collision_map_w;
}

void RRT2DColisionTest::setCollisionMapH(unsigned int collision_map_h)
{
    this->collision_map_h = collision_map_h;
}

void RRT2DColisionTest::setCollisionMapW(unsigned int collision_map_w)
{
    this->collision_map_w = collision_map_w;
}




