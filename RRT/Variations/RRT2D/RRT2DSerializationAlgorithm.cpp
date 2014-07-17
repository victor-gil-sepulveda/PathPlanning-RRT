/*
 * RRT2DSerializationAlgorithm.cpp
 *
 *  Created on: 29/05/2011
 *      Author: vgil
 */

#include "RRT2DSerializationAlgorithm.h"

RRT2DSerializationAlgorithm::RRT2DSerializationAlgorithm(){
	setGoalNode(NULL);
	setBackgroundImage("");
	setWidth(0);
	setHeight(0);
}

RRT2DSerializationAlgorithm::~RRT2DSerializationAlgorithm(){
}

bool RRT2DSerializationAlgorithm::do_save(vector<RRTNode*> & nodes, string path){

	_RRT_DEBUG_(_RRT_DEBUG_LOW_,
			cout<<"Saving on "<<path<<endl;
	);

	ofstream myfile;
	myfile.open(path.c_str());

	// What is going to be the path of the next image?
	setLastImage(path.substr(0,path.length()-3)+string("png"));

	RRTNode* father;

	for(unsigned int i =0; i<nodes.size();i++){
		father = dynamic_cast<RRTNode*>(nodes[i]->getFather());

		if(father){
			RRT2DConfiguration* n_conf = dynamic_cast<RRT2DConfiguration*>(nodes[i]->getData());
			RRT2DConfiguration* f_conf = dynamic_cast<RRT2DConfiguration*>(father->getData());
			myfile << n_conf->getX()<< " "<<n_conf->getY()<< " "<<f_conf->getX()<< " "<<f_conf->getY()<<endl;
		}
	}

	if(getGoalNode()){
		RRTNode* goal = getGoalNode();
		RRT2DConfiguration* g_conf = dynamic_cast<RRT2DConfiguration*>(goal->getData());
		myfile <<"goal "<<g_conf->getX()<< " "<<g_conf->getY()<<endl;
	}
	myfile.close();

	std:: stringstream command;
	command<<"python src/PathPlanning/RRT/Tools/RRT2bmp.py "<<getBackgroundImage()<<" "<<path<<" "<<getCurrentFile();



	_RRT_DEBUG_(_RRT_DEBUG_LOW_,
			cout<<"Calling python to get an image:"<<endl<<command.str()<<endl<<flush;
	);

	system(command.str().c_str());
	_RRT_DEBUG_(_RRT_DEBUG_LOW_,
			cout<<"Saved"<<endl;
	);
	return true;
}

RRTNode * RRT2DSerializationAlgorithm::getGoalNode() const{
	return goal_node;
}

void RRT2DSerializationAlgorithm::setGoalNode(RRTNode *goalNode){
	this->goal_node = goalNode;
}

bool RRT2DSerializationAlgorithm::do_save_all(){
	std:: stringstream command;
	command<<"mencoder \"mf://"<<getBasePath()<< "/*.png\" -mf w="<<getWidth()<<":h="<<getHeight()<<":fps=15:type=png -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o "<< getBasePath()<<"/all_"<<getBaseFile()<<".avi > "<< getBasePath()<<"/all_"<<getBaseFile()<<".out"<<endl;
	system(command.str().c_str());

	return true;
}

string& RRT2DSerializationAlgorithm::getLastImage(){
	return this->last_image;
}

void RRT2DSerializationAlgorithm::setLastImage(string s){
	this->last_image = s;
}

void RRT2DSerializationAlgorithm::do_clean(){
	std:: stringstream command;
	command<<"rm "<<getBasePath()<<"/"<<getBaseFile()<<"*";
	system(command.str().c_str());
}

string	RRT2DSerializationAlgorithm::getBackgroundImage	 () const{
	return this->background_image;
}

unsigned int RRT2DSerializationAlgorithm::getHeight	() const{
	return this->height;
}

unsigned int RRT2DSerializationAlgorithm::getWidth	() const{
	return this->width;
}

void RRT2DSerializationAlgorithm::setBackgroundImage(string path){
	this->background_image = path;
}

void RRT2DSerializationAlgorithm::setWidth (unsigned int w){
	this->width = w;
}

void RRT2DSerializationAlgorithm::setHeight(unsigned int h){
	this->height = h;
}


