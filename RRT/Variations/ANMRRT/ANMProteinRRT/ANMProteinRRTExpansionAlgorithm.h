/*
 * ANMProteinRRTExpansionAlgorithm.h
 *
 *  Created on: 12/06/2011
 *      Author: vgil
 */

#ifndef ANMPROTEINRRTEXPANSIONALGORITHM_H_
#define ANMPROTEINRRTEXPANSIONALGORITHM_H_

#include "../../ProteinRRT/RRTProteinExpansionAlgorithm.h"
#include "../../ProteinRRT/RRTProteinConfiguration.h"
#include "../BaseAlgorithms/UsesEigenvectorsAndEigenvalues.h"
#include "../../../../../Energy/EnergyCalculator.h"
#include "../../../../../ANM/ANMCalculator.h"
#include "ANMProteinConfiguration.h"
#include "../../../../Tools/Math/Solver.h"
#include "../../../../Tools/PathPlanningGeneralTools.h"

class ANMProteinRRTExpansionAlgorithm: public RRTProteinExpansionAlgorithm{

	public:
								ANMProteinRRTExpansionAlgorithm		( PathPlanning::Tools::ANMObjectsPackage* pack, Solver* s);
			virtual 			~ANMProteinRRTExpansionAlgorithm	();

			ANMCalculator*		getANMCalculator					();
			EnergyCalculator*	getEnergyCalculator					() const;
			MinParams*			getMinimParameters					() const;
			Minimizer*			getMinimizer						() const;
			Solver*				getSolver							() const;

	protected:
			void				set_ANM_calculator					(ANMCalculator*);
			void 				set_energy_calculator				(EnergyCalculator *energyCalculator);
			void 				set_minimization_params				(MinParams *minimParameters);
			void 				set_minimizer						(Minimizer *minimizer);
			void 				set_solver							(Solver *solver);

			virtual RRTNode*	do_expansion						(RRTNode* from, RRTNode* to);

			ANMCalculator* 		anmcalc;
			Minimizer * 		minimizer;
			MinParams * 		minim_parameters;
			EnergyCalculator *	energy_calculator;
			Solver* 			solver;

};

#endif /* ANMPROTEINRRTEXPANSIONALGORITHM_H_ */
