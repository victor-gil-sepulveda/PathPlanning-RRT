/*
 * ANMG2DNormalModeCalculator.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef ANMG2DNORMALMODECALCULATOR_H_
#define ANMG2DNORMALMODECALCULATOR_H_

#include <stdlib.h>
#include <time.h>

#include "../../Basealgorithms/NormalModeCalculator.h"
#include "../../../RRT/BaseAlgorithms/ExpansionAlgorithm.h"
#include "../../../RRT/Variations/ANMRRT/RRT2D/ANMRRT2DExpansionAlgorithm.h"

class ANMG2DNormalModeCalculator: public NormalModeCalculator {
	public:
						ANMG2DNormalModeCalculator			(unsigned int number_of_modes);
		virtual 		~ANMG2DNormalModeCalculator			();

	private:
		virtual void	calculate_modes						(ExpansionAlgorithm* exAlg);
};

#endif /* ANMG2DNORMALMODECALCULATOR_H_ */
