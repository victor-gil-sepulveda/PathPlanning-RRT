/*
 * ANMProteinRRTMetric.h
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#ifndef ANMPROTEINRRTANGMETRIC_H_
#define ANMPROTEINRRTANGMETRIC_H_

#include "../../../../BaseAlgorithms/RRTMetric.h"
#include "../ANMProteinConfiguration.h"

//-----------------------------
// Package
//-----------------------------
namespace ProteinPathPlanning{
	namespace ANMGuided{
			namespace Metrics{
//------------------------------


class AngularWeightMetric: public RRTMetric {
	public:

							AngularWeightMetric		();
				virtual 	~AngularWeightMetric	();

	private:

		double				calc_distance			(RRTNode* first, RRTNode* second);
};



//----------------------------
		};
	};
};

#endif /* ANMPROTEINRRTMETRIC_H_ */
