/*
 * RRTProteinExpansionAlgorithm.h
 *
 *  Created on: 12/06/2011
 *      Author: vgil
 */

#ifndef RRTPROTEINEXPANSIONALGORITHM_H_
#define RRTPROTEINEXPANSIONALGORITHM_H_
#include "../../BaseAlgorithms/ExpansionAlgorithm.h"


class RRTProteinExpansionAlgorithm : public ExpansionAlgorithm {
	public:
					RRTProteinExpansionAlgorithm	(RRTMetric* m);
		virtual 	~RRTProteinExpansionAlgorithm	();

};

#endif /* RRTPROTEINEXPANSIONALGORITHM_H_ */
