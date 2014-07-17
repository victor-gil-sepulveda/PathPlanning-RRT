/*
 * RRT.cpp
 *
 *  Created on: May 24, 2011
 *      Author: vgil
 */

#include "RRT.h"

RRT::RRT(   RRTMetric* metric,
			SamplingAlgorithm* sampAlg,
			ExpansionAlgorithm* expAlg,
			NearestNeighbourAlgorithm* nnAlg,
			ColisionTest* colTest,
			CompletionCheck* compCheck,
			RRTSerializationAlgorithm* rwAlgorithm ){


	setStartNode(NULL);

	setMetric(metric);
	setSamplingAlgorithm(sampAlg);
	setExpansionAlgorithm(expAlg);
	setNearestNeighbourAlgorithm(nnAlg);
	setColisionTestAlgorithm(colTest);
	setCompletionCheck(compCheck);
	setRwAlgorithm(rwAlgorithm);
}


RRT::~RRT(){
	destroy();
}

void  RRT::destroy(){
	for (unsigned int i = 0; i < nodes.size(); i++){
		delete nodes[i];
	}
	nodes.clear();
}



void RRT::setStartNode(RRTNode* start){
	this->start = start;
}


RRTNode*  RRT::getStartNode(){
	return start;
}


void  RRT::add_node(RRTNode* father, RRTNode* son){
	father->addSon(son);
	nodes.push_back(son);
}


void  RRT::run(RRTNode* s){
	cout<<"[RRT Run Started]"<<endl;

	// Reset the tree
	destroy();

	// Set starting node
	if(s){
		setStartNode(s);
	}
	else{
		if(!getStartNode()){
			cout<<"[RRT ERROR]: You need to define a starting node. Run aborted.";
			return;
		}
	}

	// Put steps to 0
	compCheck->resetSteps();

	// Init the next run
	RRTNode* qNew = getStartNode();
	nodes.push_back(qNew);
	nodes.reserve(compCheck->getMaxSteps());

	// START TIMERS
	TIMER_CREATE(RRT);
	TIMER_CREATE(CollisionDetection)
	TIMER_CREATE(Sampling)
	TIMER_CREATE(NearestNeighbour)
	TIMER_CREATE(Extension)
	TIMER_CREATE(Serialization)


	// START ALGORITHM
	TIMER_MEASURE(RRT,
		while(!compCheck->checkCompletion(qNew)){

			_RRT_DEBUG_(_RRT_DEBUG_LOW_,
					cout<<"Creating a random node"<<endl;
			);

			TIMER_MEASURE(Sampling,
					RRTNode* qRand = getSamplingAlgorithm()->sample(getStartNode());
			);

			_RRT_DEBUG_(_RRT_DEBUG_LOW_,
					cout<<"Finding nearest neighbor"<<endl;
			);

			TIMER_MEASURE(NearestNeighbour,
					RRTNode* qNear = getNearestNeighbourAlgorithm()->getNearestNeighbour(getNodes(),qRand);
			);

			_RRT_DEBUG_(_RRT_DEBUG_LOW_,
						cout<<"Generating new configuration"<<endl;
			);

			TIMER_MEASURE(Extension,
					qNew = getExpansionAlgorithm()->expand(qNear,qRand);
			);

			if(qNew){
				TIMER_MEASURE(CollisionDetection,
						bool colision = getColisionTestAlgorithm()->testCollision(qNew);
				);

				if(!colision){

					_RRT_DEBUG_(_RRT_DEBUG_LOW_,
								cout<<"Adding to the tree"<<endl;
					);

					add_node(qNear,qNew);
					getCompletionCheck()->increaseSucessfulSteps();

					_RRT_DEBUG_(_RRT_DEBUG_LOW_,
								cout<<"Saving tree..."<<endl;
					);

					TIMER_MEASURE(Serialization,
							if(getRwAlgorithm()){
								getRwAlgorithm()->saveState(getNodes());
							}
					);

					_RRT_DEBUG_(_RRT_DEBUG_MEDIUM_ ,
						double dist = getMetric()->calcDistance(qNear,qNew);
						cout<<"Distance: "<<dist<<endl;
						cout<<"qRand "<<*qRand<< endl;
						cout<<"qNear "<<*qNear<< endl;
						cout<<"qNew "<<*qNew<< endl;
					);
				}
				else{
					delete qNew;
					qNew = NULL;

					_RRT_DEBUG_(_RRT_DEBUG_LOW_,
						cout<<"Impossible to place node."<<endl;
					);
				}
			}

			getCompletionCheck()->increaseSteps();

			delete qRand;
		}
	);

	TIMER_MEASURE(Serialization,
		if(getRwAlgorithm()){
			getRwAlgorithm()->saveAllStates();
		}
	);

	TIMER_REPORT(RRT);
	TIMER_REPORT(Sampling);
	TIMER_REPORT(CollisionDetection);
	TIMER_REPORT(Extension);
	TIMER_REPORT(NearestNeighbour);
	TIMER_REPORT(Serialization);

	cout<<" - Ran "<<compCheck->getCurrentSteps()<<" steps, "<<compCheck->getCurrentSuccessfulSteps()<<" ended placing a point."<<endl;
	cout<<"[RRT Run Ended]"<<endl;
}



ColisionTest *RRT::getColisionTestAlgorithm() const
{
    return colTest;
}

ExpansionAlgorithm *RRT::getExpansionAlgorithm() const
{
    return expAlg;
}


RRTMetric *RRT::getMetric() const
{
    return metric;
}

NearestNeighbourAlgorithm *RRT::getNearestNeighbourAlgorithm() const
{
    return nnAlg;
}

vector<RRTNode*>& RRT::getNodes(){
    return nodes;
}

RRTSerializationAlgorithm *RRT::getRwAlgorithm() const
{
    return rwAlgorithm;
}

SamplingAlgorithm *RRT::getSamplingAlgorithm() const
{
    return sampAlg;
}

CompletionCheck* RRT::getCompletionCheck() const{
	return compCheck;
}


void RRT::setColisionTestAlgorithm(ColisionTest *colTest)
{
    this->colTest = colTest;
}

void RRT::setExpansionAlgorithm(ExpansionAlgorithm *expAlg)
{
    this->expAlg = expAlg;
}


void RRT::setMetric(RRTMetric *metric)
{
    this->metric = metric;
}

void RRT::setNearestNeighbourAlgorithm(NearestNeighbourAlgorithm *nnAlg)
{
    this->nnAlg = nnAlg;
}


void RRT::setRwAlgorithm(RRTSerializationAlgorithm *rwAlgorithm)
{
    this->rwAlgorithm = rwAlgorithm;
}

void RRT::setSamplingAlgorithm(SamplingAlgorithm *sampAlg)
{
    this->sampAlg = sampAlg;
}

void RRT::setCompletionCheck(CompletionCheck* compCheck){
	this->compCheck = compCheck;
}
