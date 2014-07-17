/*
 * RRT2DCompletionCheck.h
 *
 *  Created on: 28/05/2011
 *      Author: vgil
 */

#ifndef RRT2DCOMPLETIONCHECK_H_
#define RRT2DCOMPLETIONCHECK_H_

#include "../../BaseAlgorithms/CompletionCheck.h"
#include "RRT2DMetric.h"


class RRT2DCompletionCheck: public CompletionCheck {
	public:
						RRT2DCompletionCheck		(RRT2DMetric* m);
		virtual 		~RRT2DCompletionCheck		();

	private:
		virtual bool	do_check_completion			(RRTNode* node);
};

#endif /* RRT2DCOMPLETIONCHECK_H_ */
