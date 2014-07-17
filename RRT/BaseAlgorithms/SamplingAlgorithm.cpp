/*
 * SamplingAlgorithm.cpp
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#include "SamplingAlgorithm.h"

SamplingAlgorithm::SamplingAlgorithm(bool save_random){
	this->save_random = save_random;
	this->current_random = 0;
	setDimension(0);
}

SamplingAlgorithm::~SamplingAlgorithm(){

}


RRTNode* SamplingAlgorithm::sample(RRTNode *initial){

	// If there are more random numbers stored than the current number,
	// we consume them
	vector<int> random;

	for (unsigned int i = 0; i < getDimension(); ++i) {
		if(random_numbers.size()>current_random){
			random.push_back(consume_random());
		}
		else{
			random.push_back(gen_random());
			if(save_random){
				random_numbers.push_back(random[i]);
			}
		}
		current_random++;
	}

	return do_sample(initial, random);
}


vector<int>& SamplingAlgorithm::getRandomNumbers (){
	return random_numbers;
}

void SamplingAlgorithm::setRandomNumbers(vector<int> & numbers){
	copy(numbers.begin(),numbers.end(),this->getRandomNumbers().begin());
	this->current_random = 0;
}

bool SamplingAlgorithm::saveRandomNumbers(string path){

	std:: stringstream stream;

	for(unsigned int i =0; i < random_numbers.size(); i++){
		stream<<random_numbers[i]<<endl;
	}

	Utils::ossToFile(path.c_str(),stream.str());

	return random_numbers.size() != 0;
}

bool SamplingAlgorithm::loadRandomNumbers(string path){
	random_numbers.clear();
	current_random = 0;

	int i = 0;
	string line;
	ifstream myfile (path.c_str());
	if (myfile.is_open()){
		while(! myfile.eof())
		{
			getline(myfile, line);
			if(line.size()>0){
				random_numbers.push_back(atoi(line.c_str()));
				i++;
			}
		}
		cout<<i<<" lines read."<<flush<<endl;
		myfile.close();
		return true;
	}
	else{
		cout << "Unable to open file: "<< path << flush<< endl;
		return false;
	}
}

// Uses a random number previously stored
int SamplingAlgorithm::consume_random(){
	return random_numbers[current_random];
}



unsigned int SamplingAlgorithm::getDimension() const{
	return dimension;
}

void SamplingAlgorithm::setDimension(unsigned int d){
	this->dimension = d;
}





