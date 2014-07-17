/*
 * NormalModeCalculator.h
 *
 *  Created on: Jun 7, 2011
 *      Author: vgil
 */

#ifndef NORMALMODECALCULATOR_H_
#define NORMALMODECALCULATOR_H_

#include "../../RRT/BaseAlgorithms/ExpansionAlgorithm.h"

class NormalModeCalculator : public RRTBaseAlgorithm {

	public:
							NormalModeCalculator		(unsigned int number_of_modes);
		virtual 			~NormalModeCalculator		();

		unsigned int 		getNumberOfModes			() const;
		void 				setNumberOfModes			(unsigned int numberOfModes);
		void				calculateModes				(ExpansionAlgorithm* exAlg);
	private:

		virtual void		calculate_modes				(ExpansionAlgorithm* exAlg)=0;

		unsigned int 		number_of_modes;
};

#endif /* NORMALMODECALCULATOR_H_ */
