/*
 * CompletionCheck.cpp
 *
 *  Created on: 27/05/2011
 *      Author: vgil
 */

#include "CompletionCheck.h"

CompletionCheck::CompletionCheck(RRTMetric* m) : metric(m){
	setMaxSteps(0);
	setMaxSuccessfulSteps(0);
	setGoal(NULL);
	resetSteps();
}

CompletionCheck::~CompletionCheck() {
}

bool CompletionCheck::checkCompletion(RRTNode* node){
	return do_check_completion(node);
}

RRTNode * CompletionCheck::getGoal() const
{
	return goal;
}

RRTMetric * CompletionCheck::getMetric() const
{
	return metric;
}

unsigned int CompletionCheck::getMaxSteps() const
{
	return steps;
}

unsigned int CompletionCheck::getMaxSuccessfulSteps() const
{
	return successful_steps;
}

void CompletionCheck::setGoal(RRTNode *goal)
{
	this->goal = goal;
}

void CompletionCheck::setMetric(RRTMetric *metric)
{
	this->metric = metric;
}

void CompletionCheck::setMaxSteps(unsigned int steps)
{
	this->steps = steps;
	if(this->steps>this->successful_steps){
		setMaxSuccessfulSteps(steps);
	}
}

void CompletionCheck::increaseSteps(){
	current_steps++;
}

void CompletionCheck::increaseSucessfulSteps(){
	current_successful_steps++;
}

void CompletionCheck::resetSteps(){
	current_steps = current_successful_steps = 0;
}

unsigned int CompletionCheck::getCurrentSteps() const{
	return current_steps;
}

unsigned int CompletionCheck::getCurrentSuccessfulSteps() const{
	return current_successful_steps;
}

void CompletionCheck::setMaxSuccessfulSteps(unsigned int successful_steps)
{
	this->successful_steps = successful_steps;
}


