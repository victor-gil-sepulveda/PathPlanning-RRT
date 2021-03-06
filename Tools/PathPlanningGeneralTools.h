/*
 * PathPlanningGeneralTools.h
 *
 *  Created on: 01/07/2011
 *      Author: victor
 */

#ifndef PATHPLANNINGGENERALTOOLS_H_
#define PATHPLANNINGGENERALTOOLS_H_
#include "jsoncpp/json.h"
#include "../../Molecules/Complex.h"
#include "../../Molecules/Solvent/Solvent.h"
#include "../../Energy/PotentialConstraint/ConstraintParams/ConstraintParams.h"
#include "../../Energy/EnergyCalculator.h"
#include "../../Minimizers/Parameters/MinParams.h"
#include "../../Minimizers/Minimizer.h"
#include "../../ANM/Parameters/ANM_Params.h"
#include "../../ANM/ANMCalculator.h"
#include "../../Minimizers/MinimizerBuilder.h"
#include "../../ANM/ANMCalculatorBuilder.h"
#include "../../System/System.h"

namespace PathPlanning{
	namespace Tools{

		class ANMObjectsPackage{
			public:
				ANMObjectsPackage(System* sys,Complex * c, Solvent* solv);
				~ANMObjectsPackage();

				void populateANMObjects(const char* conf_source);

				// TODO :: HACER GETTERS

				System* system;
				Complex * complex;
				Solvent* solvent;
				ConstraintParams* constraintParams;
				EnergyCalculator* energyCalculator;
				MinParams* anmMinParameters;
				Minimizer* anmMinimizer;
				ANM_Params * anmParameters;
				ANMCalculator * anmCalculator;
		};
	};
};

#endif /* PATHPLANNINGGENERALTOOLS_H_ */
