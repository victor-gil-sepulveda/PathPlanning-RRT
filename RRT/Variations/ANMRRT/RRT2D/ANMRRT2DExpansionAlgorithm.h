/*
 * ANMRRT2DExpansionAlgorithm.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef ANMRRT2DEXPANSIONALGORITHM_H_
#define ANMRRT2DEXPANSIONALGORITHM_H_


#include "../../../Variations/RRT2D/RRT2DExpansionAlgorithm.h"
#include "../../../RRTConfiguration.h"
#include "../BaseAlgorithms/UsesEigenvectorsAndEigenvalues.h"
#include "ANMRRT2DConfiguration.h"
#include "ANMRRT2DMetric.h"




class ANMRRT2DExpansionAlgorithm : public RRT2DExpansionAlgorithm,
										public UsesEigenvectorsAndEigenvalues{

	public:

									ANMRRT2DExpansionAlgorithm		(ANMRRT2DMetric* m = NULL);
		virtual 					~ANMRRT2DExpansionAlgorithm		();

	private:

		virtual RRTNode* 			do_expansion					(RRTNode* from, RRTNode* to);
};

#endif /* ANMRRT2DEXPANSIONALGORITHM_H_ */
