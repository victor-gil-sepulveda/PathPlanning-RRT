/*
 * RRTSerializationAlgorithm.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "RRTSerializationAlgorithm.h"

RRTSerializationAlgorithm::RRTSerializationAlgorithm() {
	setBasePath("");
	setCurrentFile(0);
	setBaseFile("");
	setFileType("");
	setMaxFiles(0);
	setClean(false);
	setSaveAllStates(true);
	setSaveState(true);
	max_ciphers = 0;
	path=string("");
}

RRTSerializationAlgorithm::~RRTSerializationAlgorithm() {
}

string RRTSerializationAlgorithm::getBasePath() const{
	return base_path;
}

unsigned int RRTSerializationAlgorithm::getCurrentFile() const{
	return current_file;
}

void RRTSerializationAlgorithm::setBasePath(string basePath){
	this->base_path = basePath;
}

bool RRTSerializationAlgorithm::saveState(vector<RRTNode*> & nodes){

	if(getSaveState()){
		string mypath;
		std:: stringstream stream;
		stream.width(get_max_numb());
		stream.fill('0');
		stream << getCurrentFile();

		this->path = getBasePath()+string("/")+getBaseFile()+stream.str()+((getFileType()!=string(""))?string(".")+getFileType():string(""));

		setCurrentFile(getCurrentFile()+1);

		return do_save(nodes,this->path);
	}

	return true;
}

void RRTSerializationAlgorithm::setCurrentFile(unsigned int currentFile){
	this->current_file = currentFile;
}

bool RRTSerializationAlgorithm::saveAllStates(){
	if(getSaveAllStates()){
		bool success =  do_save_all();
		if (getClean()) do_clean ();

		return success;
	}
	return true;
}

int RRTSerializationAlgorithm::get_max_numb(){
	int nfil = getMaxFiles()==0?getCurrentFile():getMaxFiles();
	int ncip = 0;
	do{
		ncip++;
		nfil = nfil / 10;
	}
	while(nfil);

	return ncip;
}

string RRTSerializationAlgorithm::getBaseFile() const{
	return base_file;
}

unsigned int RRTSerializationAlgorithm::getMaxFiles() const{
	return max_files;
}

void RRTSerializationAlgorithm::setBaseFile(string baseFile){
	this->base_file = baseFile;
}

void RRTSerializationAlgorithm::setMaxFiles(unsigned int maxFiles){

	this->max_files = maxFiles;
	// get the maximum number of ciphers
	get_max_numb();
}

string RRTSerializationAlgorithm::getFileType() const
{
	return file_type;
}

void RRTSerializationAlgorithm::setFileType(string fileType)
{
	this->file_type = fileType;
}


bool RRTSerializationAlgorithm::getClean () const{
	return clean_the_room;
}


void RRTSerializationAlgorithm::setClean (bool clean){
	this->clean_the_room =  clean;
}


string	RRTSerializationAlgorithm::getLastFilePath(){
	return this->path;
}

bool RRTSerializationAlgorithm::getSaveAllStates() const
{
    return save_all_states;
}

bool RRTSerializationAlgorithm::getSaveState() const
{
    return save_state;
}

void RRTSerializationAlgorithm::setSaveAllStates(bool save_all_states)
{
    this->save_all_states = save_all_states;
}

void RRTSerializationAlgorithm::setSaveState(bool save_state)
{
    this->save_state = save_state;
}


