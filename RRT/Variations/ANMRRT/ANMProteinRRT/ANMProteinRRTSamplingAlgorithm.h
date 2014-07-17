/*
 * ANMProteinRRTSamplingAlgorithm.h
 *
 *  Created on: 06/07/2011
 *      Author: victor
 */

#ifndef ANMPROTEINRRTSAMPLINGALGORITHM_H_
#define ANMPROTEINRRTSAMPLINGALGORITHM_H_

#include "../../../BaseAlgorithms/SamplingAlgorithm.h"
#include <time.h>
#include <stdlib.h>
#include "ANMProteinConfiguration.h"


class ANMProteinRRTSamplingAlgorithm: public SamplingAlgorithm {

	public:
							ANMProteinRRTSamplingAlgorithm		(bool save_random = false);
		virtual 			~ANMProteinRRTSamplingAlgorithm		();

		void				setBoundaries						(BoundDescriptor* b);
		BoundDescriptor* 	getBoundaries						();

	private:

		int				 gen_random								();
		RRTNode*		 do_sample								(RRTNode* initial, vector<int>& rand_num);

		BoundDescriptor* boundaries;
};


#endif /* ANMPROTEINRRTSAMPLINGALGORITHM_H_ */
