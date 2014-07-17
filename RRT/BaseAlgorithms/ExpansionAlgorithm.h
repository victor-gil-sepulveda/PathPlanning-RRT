/*
 * ExpansionAlgorithm.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef EXPANSIONALGORITHM_H_
#define EXPANSIONALGORITHM_H_

#include "RRTBaseAlgorithm.h"
#include "RRTMetric.h"


class ExpansionAlgorithm: public RRTBaseAlgorithm {
	public:
							ExpansionAlgorithm	(RRTMetric* m = NULL);
		virtual 			~ExpansionAlgorithm	();

		RRTNode*			expand				(RRTNode* from, RRTNode* to);
		RRTMetric *			getMetric			() const;
		void 				setMetric			(RRTMetric *metric);

	protected:
		virtual RRTNode*	do_expansion			(RRTNode* from, RRTNode* to) = 0;
		RRTMetric* metric;

};

#endif /* EXPANSIONALGORITHM_H_ */
