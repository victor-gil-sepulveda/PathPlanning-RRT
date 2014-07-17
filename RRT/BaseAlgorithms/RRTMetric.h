/*
 * RRTMetric.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef RRTMETRIC_H_
#define RRTMETRIC_H_

#include "RRTBaseAlgorithm.h"

#include <cmath>

class RRTMetric: public RRTBaseAlgorithm{

	public:
						RRTMetric	 	();
		virtual 		~RRTMetric	 	();

		double 			calcDistance 	(RRTNode* first, RRTNode* second);
		bool			closeTo		 	(RRTNode *first, RRTNode *second);
		bool			overlaps		(RRTNode *first, RRTNode *second);

		void			setTolerance	(double tol);
		double 			getTolerance	();

	protected:

		virtual double	calc_distance	(RRTNode* first, RRTNode* second) = 0;

		double	tolerance;
};

#endif /* RRTMETRIC_H_ */
