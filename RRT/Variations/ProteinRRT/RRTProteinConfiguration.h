/*
 * ProteinConfiguration.h
 *
 *  Created on: 11/06/2011
 *      Author: vgil
 */

#ifndef PROTEINCONFIGURATION_H_
#define PROTEINCONFIGURATION_H_

#include "../../RRTConfiguration.h"
#include "../../../../Molecules/AtomSet/AtomSet.h"

class RRTProteinConfiguration: public RRTConfiguration {
	public:
							RRTProteinConfiguration	(AtomSet* 	p);
		virtual 			~RRTProteinConfiguration();

		double*				getStateCoordinates		();
		unsigned int 		getCoordinatesSize		() const;
		AtomSet*			getProtein				();

	protected:

		void				set_protein				(AtomSet* p);

		// To store current coordinates state
		// We still use double because a number bigger than 99 could
		// produce an overflow
		double* state_coordinates;
		unsigned int size_coordinates;

		// The protein which space we are sampling
		AtomSet* 	protein;

};

#endif /* PROTEINCONFIGURATION_H_ */
