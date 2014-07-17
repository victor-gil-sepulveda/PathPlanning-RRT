/*
 * RRT2DCompletionCheck.cpp
 *
 *  Created on: 28/05/2011
 *      Author: vgil
 */

#include "RRT2DCompletionCheck.h"

RRT2DCompletionCheck::RRT2DCompletionCheck(RRT2DMetric* m): CompletionCheck(dynamic_cast<RRTMetric*>(m)) {
}

RRT2DCompletionCheck::~RRT2DCompletionCheck() {
}

bool RRT2DCompletionCheck::do_check_completion(RRTNode* node){
	bool goal_reached = false;
	if(getGoal() && node) goal_reached = getMetric()->closeTo(node,getGoal());

	bool steps_completed = getMaxSteps()==0?false:(getMaxSteps()<=current_steps);

	bool suc_steps_completed = getMaxSuccessfulSteps()!=0?(getMaxSuccessfulSteps()<=current_successful_steps):false;

	_RRT_DEBUG_(_RRT_DEBUG_HIGH_,
		cout<< "Goal is "<<*getGoal()<<endl;
		if(!node){
			cout<< "Last node was NULL (so it was no possible to place it)"<<flush<<endl;
		}
		else{
			cout<< "Last node was "<<*node<<flush<<endl;
			cout<< "Distance between them is "<<getMetric()->calcDistance(getGoal(),node)<<flush<<endl;
			cout<< "Close to ( with tolerance "<<getMetric()->getTolerance()<<" ) says "<<(getMetric()->closeTo(node,getGoal())?string("true"):string("false"))<<flush<<endl;
		}
		cout<< "And thus 'goal_reached' is "<<(goal_reached?string("true"):string("false"))<<flush<<endl;
		cout<< getCurrentSteps()<< " steps were performed, for a maximum of "<<getMaxSteps()<<flush<<endl;
		cout<< getCurrentSuccessfulSteps()<< " successful steps were performed, for a maximum of "<<getMaxSuccessfulSteps()<<flush<<endl;
		cout<<"Then 'steps_completed' is "<<(steps_completed?string("true"):string("false"))<<" and 'suc_steps_completed' is "<<(suc_steps_completed?string("true"):string("false"))<<flush<<endl;
	);


	return steps_completed || suc_steps_completed || goal_reached;
}


