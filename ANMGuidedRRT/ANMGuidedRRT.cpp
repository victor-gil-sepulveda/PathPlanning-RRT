/*
 * ANMGuidedRRT.cpp
 *
 *  Created on: Jun 6, 2011
 *      Author: vgil
 */

#include "ANMGuidedRRT.h"

ANMGuidedRRT::ANMGuidedRRT(	RRT* rrt,  				NormalModeCalculator* nc,
							RRTMetric* m,			StartNodePicker* sp,
							CompletionCheck* cc,	RRTSerializationAlgorithm* ser) {
	setTree(rrt);
	setNormalModeCalculator(nc);
	setMetric(m);
	setNodePicker(sp);
	setCompletionCheck(cc);
	setSerializationAlgorithm(ser);
	start = NULL;
}

ANMGuidedRRT::~ANMGuidedRRT() {

}

void ANMGuidedRRT::reset(){
	nodes.clear();
	if(comp_check){
		comp_check->resetSteps();
	}
}

void ANMGuidedRRT::run(RRTNode* alt_start){

	// reset everything
	reset();

	// Handle starting node
	if(alt_start){
		setStartNode(alt_start);
	}
	else{
		if(!getStartNode()){
			cout<<"[ANM Guided RRT ERROR]: You need to define a starting node. Run aborted.";
			return;
		}
	}

	// Start the algorithm
	RRTNode* qNewStart = getStartNode();
	nodes.push_back(qNewStart);
	nodes.reserve(getCompletionCheck()->getMaxSteps());

	while(!getCompletionCheck()->checkCompletion(qNewStart)){

		// Calculate normal modes
		getNormalModeCalculator()->calculateModes(getTree()->getExpansionAlgorithm());

		// Run RRT for the calculated modes
		getTree()->run(qNewStart);

		// Add the nodes of the RRT to the global nodes vector
		vector<RRTNode*>& rrtnodes = getTree()->getNodes();
		this->nodes.insert(this->nodes.end(),rrtnodes.begin(),rrtnodes.end());
		// if you do not do the clear then the reset operation is going to
		// destroy all the nodes, leading to chaos
		rrtnodes.clear();

		// Pick the new starting node
		qNewStart = getNodePicker()->pickNewStartingNode(this->nodes);

		getCompletionCheck()->increaseSteps();

		if(getSerializationAlgorithm()){
			getSerializationAlgorithm()->saveState(this->nodes);
		}
	}

	if(getSerializationAlgorithm()){
		getSerializationAlgorithm()->saveAllStates();
	}
}

CompletionCheck *ANMGuidedRRT::getCompletionCheck() const
{
    return comp_check;
}

RRTMetric *ANMGuidedRRT::getMetric() const
{
    return metric;
}

StartNodePicker *ANMGuidedRRT::getNodePicker() const
{
    return node_picker;
}

vector<RRTNode*> ANMGuidedRRT::getNodes() const
{
    return nodes;
}

RRTSerializationAlgorithm *ANMGuidedRRT::getSerializationAlgorithm() const
{
    return ser_algorithm;
}

RRTNode *ANMGuidedRRT::getStartNode() const
{
    return start;
}

RRT *ANMGuidedRRT::getTree() const
{
    return tree;
}

NormalModeCalculator* ANMGuidedRRT::getNormalModeCalculator() const
{
	return this->normal_mode_calculator;
}

void ANMGuidedRRT::setCompletionCheck(CompletionCheck *compCheck)
{
    this->comp_check = compCheck;
}

void ANMGuidedRRT::setMetric(RRTMetric *metric)
{
    this->metric = metric;
}

void ANMGuidedRRT::setNodePicker(StartNodePicker *nodePicker)
{
    this->node_picker = nodePicker;
}

void ANMGuidedRRT::setNodes(vector<RRTNode*> nodes)
{
    this->nodes = nodes;
}

void ANMGuidedRRT::setSerializationAlgorithm(RRTSerializationAlgorithm *serAlgorithm)
{
    this->ser_algorithm = serAlgorithm;
}

void ANMGuidedRRT::setStartNode(RRTNode *start)
{
    this->start = start;
}

void ANMGuidedRRT::setTree(RRT *tree)
{
    this->tree = tree;
}

void ANMGuidedRRT::setNormalModeCalculator(NormalModeCalculator *nc)
{
	this->normal_mode_calculator = nc;
}








