/*
 * ANMGuidedRRT.h
 *
 *  Created on: Jun 6, 2011
 *      Author: vgil
 */

#ifndef ANMGUIDEDRRT_H_
#define ANMGUIDEDRRT_H_

#include "../RRT/BaseAlgorithms/RRTMetric.h"
#include "../RRT/BaseAlgorithms/CompletionCheck.h"
#include "../RRT/BaseAlgorithms/RRTSerializationAlgorithm.h"
#include "../RRT/RRTNode.h"
#include "../RRT/RRT.h"

#include "Basealgorithms/StartNodePicker.h"
#include "Basealgorithms/NormalModeCalculator.h"

#include "../../Tools/vectorTools.h"

class NormalModeCalculator;

class ANMGuidedRRT {

	public:

									ANMGuidedRRT		(
															RRT* rrt,
															NormalModeCalculator* nc,
															RRTMetric* m,
															StartNodePicker* sp,
															CompletionCheck* cc,
															RRTSerializationAlgorithm* ser
														);
		virtual 					~ANMGuidedRRT		();

		void 						run					(RRTNode* alt_start = NULL);
		void						reset				();

		CompletionCheck *			getCompletionCheck			() const;
		RRTMetric *					getMetric					() const;
		StartNodePicker *			getNodePicker				() const;
		vector<RRTNode*> 			getNodes					() const;
		RRTSerializationAlgorithm *	getSerializationAlgorithm	() const;
		RRTNode *					getStartNode				() const;
		RRT *						getTree						() const;
		NormalModeCalculator*		getNormalModeCalculator		() const;

		void 		setCompletionCheck			(CompletionCheck *compCheck);
		void 		setMetric					(RRTMetric *metric);
		void 		setNodePicker				(StartNodePicker *nodePicker);
		void 		setNodes					(vector<RRTNode*> nodes);
		void 		setSerializationAlgorithm	(RRTSerializationAlgorithm *serAlgorithm);
		void 		setStartNode				(RRTNode *start);
		void 		setTree						(RRT *tree);
		void		setNormalModeCalculator 	(NormalModeCalculator* nc);

	private:

		RRT* tree;
		RRTSerializationAlgorithm* ser_algorithm;
		CompletionCheck* comp_check;
		RRTMetric*	metric;
		StartNodePicker* node_picker;
		vector<RRTNode*> nodes;
		RRTNode* start;
		NormalModeCalculator* normal_mode_calculator;
};

#endif /* ANMGUIDEDRRT_H_ */
