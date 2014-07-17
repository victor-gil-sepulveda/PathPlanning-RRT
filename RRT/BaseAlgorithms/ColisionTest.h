/*
 * ColisionTest.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef COLISIONTEST_H_
#define COLISIONTEST_H_

#include "RRTBaseAlgorithm.h"
#include "RRTMetric.h"

class ColisionTest: public RRTBaseAlgorithm {
	public:
							ColisionTest			(RRTMetric* m = NULL);
		virtual 			~ColisionTest			();

		bool				testCollision			(RRTNode* node);
		RRTMetric 			*getMetric				() const;
		void 				setMetric				(RRTMetric *metric);



	protected:
		virtual bool 		test_collision			(RRTNode* node) = 0;
		RRTMetric* 			metric;
};

#endif /* COLISIONTEST_H_ */
