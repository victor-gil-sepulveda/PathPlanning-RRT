/*
 * ANMRRT2DMetric.h
 *
 *  Created on: Jun 8, 2011
 *      Author: vgil
 */

#ifndef ANMRRT2DMETRIC_H_
#define ANMRRT2DMETRIC_H_

#include "../../../Variations/RRT2D/RRT2DMetric.h"
#include "ANMRRT2DConfiguration.h"


class ANMRRT2DMetric: public RRT2DMetric {

	public:
		ANMRRT2DMetric();
		virtual ~ANMRRT2DMetric();

	private:
		virtual double	calc_distance	(RRTNode* first, RRTNode* second);
};

#endif /* ANMRRT2DMETRIC_H_ */
