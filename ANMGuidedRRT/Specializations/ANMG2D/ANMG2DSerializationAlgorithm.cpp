/*
 * ANMG2DSerializationAlgorithm.cpp
 *
 *  Created on: Jun 9, 2011
 *      Author: vgil
 */

#include "ANMG2DSerializationAlgorithm.h"

ANMG2DSerializationAlgorithm::ANMG2DSerializationAlgorithm() {
}

ANMG2DSerializationAlgorithm::~ANMG2DSerializationAlgorithm() {
}

bool ANMG2DSerializationAlgorithm::do_save(vector<RRTNode*> & nodes, string path){
	RRT2DSerializationAlgorithm* ser = dynamic_cast<RRT2DSerializationAlgorithm*>(getTreeSerializer());
	ser->setBackgroundImage(ser->getLastImage());
	return true;
}

RRTSerializationAlgorithm *ANMG2DSerializationAlgorithm::getTreeSerializer() const
{
    return tree_serializer;
}

void ANMG2DSerializationAlgorithm::setTreeSerializer(RRTSerializationAlgorithm *tree_serializer)
{
    this->tree_serializer = tree_serializer;
}

void ANMG2DSerializationAlgorithm::do_clean(){
	RRT2DSerializationAlgorithm* ser = dynamic_cast<RRT2DSerializationAlgorithm*>(getTreeSerializer());
	std:: stringstream command;
	command<<"rm "<<ser->getBasePath()<<"/"<<ser->getBaseFile()<<"*";
	system(command.str().c_str());
}

bool ANMG2DSerializationAlgorithm::do_save_all(){
	RRT2DSerializationAlgorithm* ser = dynamic_cast<RRT2DSerializationAlgorithm*>(getTreeSerializer());
	std:: stringstream command;
	command<<"mencoder \"mf://"<<ser->getBasePath()<< "/*.png\" -mf w="<<ser->getWidth()<<":h="<<ser->getHeight()<<":fps=15:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o "<< ser->getBasePath()<<"/all_anmg_"<<ser->getBaseFile()<<".avi > "<< ser->getBasePath()<<"/all_anmg_"<<ser->getBaseFile()<<".out"<<endl;
	system(command.str().c_str());
	return true;
}


