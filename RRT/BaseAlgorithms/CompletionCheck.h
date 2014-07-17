/*
 * CompletionCheck.h
 *
 *  Created on: 27/05/2011
 *      Author: vgil
 */

#ifndef COMPLETIONCHECK_H_
#define COMPLETIONCHECK_H_

#include "../RRTNode.h"
#include "RRTBaseAlgorithm.h"
#include "RRTMetric.h"


class CompletionCheck : public RRTBaseAlgorithm {

		public:
								CompletionCheck			(RRTMetric* m = NULL);
			virtual 			~CompletionCheck		();

			void				increaseSteps			();
			void				increaseSucessfulSteps	();

			void				resetSteps				();

			bool 				checkCompletion				(RRTNode* node);

			RRTNode*			getGoal						() const;
			RRTMetric *			getMetric					() const;
			unsigned int 		getMaxSteps					() const;
			unsigned int 		getMaxSuccessfulSteps			() const;
			unsigned int 		getCurrentSteps				() const;
			unsigned int 		getCurrentSuccessfulSteps	() const;


			void 				setGoal					(RRTNode *goal);
			void 				setMetric				(RRTMetric *metric);
			void 				setMaxSteps				(unsigned int steps);
			void 				setMaxSuccessfulSteps		(unsigned int successful_steps);

		protected:
			virtual bool 		do_check_completion		(RRTNode* node)=0;
			RRTMetric* 			metric;
			unsigned int		steps;
			unsigned int		successful_steps;
			RRTNode* 			goal;

			// Values for the current step
			unsigned int		current_steps;
			unsigned int		current_successful_steps;

};

#endif /* COMPLETIONCHECK_H_ */
