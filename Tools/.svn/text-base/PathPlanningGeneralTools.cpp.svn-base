/*
 * PathPlanningGeneralTools.cpp
 *
 *  Created on: 01/07/2011
 *      Author: victor
 */

#include "PathPlanningGeneralTools.h"



PathPlanning::Tools::ANMObjectsPackage::ANMObjectsPackage(System* sys, Complex * c, Solvent* solv){
	this->system = sys;
	this->complex = c;
	this->solvent = solv;
	this->constraintParams = NULL;
	this->energyCalculator = NULL;
	this->anmMinParameters = NULL;
	this->anmMinimizer = NULL;
	this->anmParameters = NULL;
	this->anmCalculator = NULL;
}

PathPlanning::Tools::ANMObjectsPackage::~ANMObjectsPackage(){
	if(this->complex) 			delete this->complex;
	if(this->solvent) 			delete this->solvent;
	if(this->constraintParams) 	delete this->constraintParams;
	if(this->energyCalculator)	delete this->energyCalculator;
	if(this->anmMinParameters) 	delete this->anmMinParameters;
	if(this->anmMinimizer) 		delete this->anmMinimizer;
	if(this->anmParameters) 	delete this->anmParameters;
	if(this->anmCalculator) 	delete this->anmCalculator;

}

void PathPlanning::Tools::ANMObjectsPackage::populateANMObjects(const char* conf_source){

	string json_contents = Utils::fileToString(conf_source);
	Json::Value root;
	Json::Reader reader;
	Json::Value dummy_general_block;

	bool parsedSuccess = reader.parse(json_contents, root, false);

	if(!parsedSuccess){
		cout << "Failed to parse JSON" << endl << reader.getFormatedErrorMessages() << endl;
		exit(1);
	}

	// Parse ANM
	Json::Value jSonANMBlock 		= JsonUtils::searchSection(dummy_general_block, root,  JsonDefaultBlockPaths::EMPTY_PATH,
																	  Configuration_ANM::BLOCK_NAME);
	// Parse Minimizer
	Json::Value jSonMinimizerBlock 	= JsonUtils::searchSection(dummy_general_block, jSonANMBlock, JsonDefaultBlockPaths::EMPTY_PATH,
																		Configuration_ANM::MINIMIZER);

	MinimizerBuilder minimizerBuilder;
	minimizerBuilder.createFromConfiguration(jSonMinimizerBlock, dummy_general_block,this->solvent, this->system,
											&(this->constraintParams), &(this->energyCalculator),
											&(this->anmMinParameters),&(this->anmMinimizer));

	ANMCalculatorBuilder anmCalculatorBuilder;

	anmCalculatorBuilder.createFromConfiguration(jSonANMBlock, NULL, NULL, NULL,
			&(this->anmParameters), &(this->anmCalculator));

}
