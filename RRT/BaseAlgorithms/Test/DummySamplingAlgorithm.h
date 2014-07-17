/*
 * DummySamplingAlgorithm.h
 *
 *  Created on: May 30, 2011
 *      Author: vgil
 */

#ifndef DUMMYSAMPLINGALGORITHM_H_
#define DUMMYSAMPLINGALGORITHM_H_

#include "../SamplingAlgorithm.h"

class DummySamplingAlgorithm: public SamplingAlgorithm {
		public:
			DummySamplingAlgorithm():SamplingAlgorithm(true){
				num = 0;
			}
			virtual ~DummySamplingAlgorithm(){

			}

			virtual	int	gen_random (){

				num++;

				return num-1;
			}

			virtual RRTNode* do_sample (RRTNode* initial, vector<int>& rand_num) {
				//Store the numbers used to do the sampling
				for(unsigned int i =0; i <rand_num.size();i++)
					sampled.push_back(rand_num[i]);
				return initial;
			}

			int consume_random(){
				return random_numbers[current_random];
			}

			vector<int>& getSampled(){
				return sampled;
			}

			void reset(){
				num =0;
				sampled.clear();
			}

		private:
			int num;
			vector<int> sampled;
};

#endif /* DUMMYSAMPLINGALGORITHM_H_ */
