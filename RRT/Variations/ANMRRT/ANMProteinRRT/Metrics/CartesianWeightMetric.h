/*
 * ANMProteinRRTMetric.h
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#ifndef ANMPROTEINRRTCARTMETRIC_H_
#define ANMPROTEINRRTCARTMETRIC_H_

#include "../../../../BaseAlgorithms/RRTMetric.h"
#include "../ANMProteinConfiguration.h"

//-----------------------------
// Package
//-----------------------------
namespace ProteinPathPlanning{
	namespace ANMGuided{
			namespace Metrics{
//------------------------------


class CartesianWeightMetric: public RRTMetric {
	public:

						CartesianWeightMetric	();
			virtual 	~CartesianWeightMetric	();

	private:

		double			calc_distance			(RRTNode* first, RRTNode* second);
};



//----------------------------
		};
	};
};

#endif /* ANMPROTEINRRTMETRIC_H_ */
