/*
 * ANMRRT2DConfiguration.h
 *
 *  Created on: Jun 8, 2011
 *      Author: vgil
 */

#ifndef ANMRRT2DCONFIGURATION_H_
#define ANMRRT2DCONFIGURATION_H_

#include <algorithm>

#include "../../RRT2D/RRT2DConfiguration.h"

class ANMRRT2DConfiguration: public RRT2DConfiguration {

	public:
								ANMRRT2DConfiguration	();
		virtual 				~ANMRRT2DConfiguration	();

		vector<double>&			getAmplitudes			();
		void 					setAmplitudes			(vector<double>& amp);


	private:

		vector<double> amplitudes;
};

#endif /* ANMRRT2DCONFIGURATION_H_ */
