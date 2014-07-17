/*
 * StartNodePicker.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef STARTNODEPICKER_H_
#define STARTNODEPICKER_H_

#include "../../RRT/BaseAlgorithms/RRTMetric.h"

class StartNodePicker : public RRTBaseAlgorithm{

	public:
							StartNodePicker			(RRTMetric* m);
		virtual 			~StartNodePicker		();

		RRTNode* 			pickNewStartingNode		(vector<RRTNode*>& nodes);
		RRTMetric *			getMetric				() const;
		RRTNode*			getGoal					() const;
		void 				setMetric				(RRTMetric *metric);
		void 				setGoal					(RRTNode* node);

	protected:
		virtual RRTNode*	pick_new_starting_node 	(vector<RRTNode*>& nodes)=0;

		RRTMetric* 	metric;
		RRTNode* 	goal;
};

#endif /* STARTNODEPICKER_H_ */
