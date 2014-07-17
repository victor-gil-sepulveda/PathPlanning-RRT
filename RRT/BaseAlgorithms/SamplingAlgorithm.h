/*
 * SamplingAlgorithm.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef SAMPLINGALGORITHM_H_
#define SAMPLINGALGORITHM_H_

#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

#include "RRTBaseAlgorithm.h"
#include "../../../Tools/Utils.h"


class SamplingAlgorithm: public RRTBaseAlgorithm {

		public:
							SamplingAlgorithm				(bool save_random = false);
			virtual 		~SamplingAlgorithm				();

			RRTNode*		sample 							(RRTNode* initial);

			vector<int>& 	getRandomNumbers				();
			void			setRandomNumbers				(vector<int>& numbers);

			unsigned int 	getDimension					() const;
			void			setDimension					(unsigned int d);

			bool			saveRandomNumbers				(string path);
			bool			loadRandomNumbers				(string path);

		protected:

			virtual 		int				gen_random		() = 0;
			virtual 		RRTNode*		do_sample		(RRTNode* initial, vector<int>& rand_num) =0;
			virtual			int				consume_random	();
			vector<int> 	random_numbers;
			bool 			save_random;
			unsigned int	current_random;
			unsigned int 	dimension;
};

#endif /* SAMPLINGALGORITHM_H_ */
