#include <cstdlib>
#include <cstring>

#include "../../../Molecules/ComplexBuilder.h"
#include "../../../System/System.h"
#include "../../Tools/PathPlanningGeneralTools.h"
#include "../../../Molecules/Solvent/SolventGenerator.h"
#include "../../../Tools/Math/MathTools.h"
#include "../../../System/SystemVars.h"
#include "ANMDataWrapper.h"


bool accepted(double e_new, double e_old,RandomGenerator& randomGen, double beta);
void iterate(PathPlanning::Tools::ANMObjectsPackage& pack, Solvent* solvent);

ANMDataWrapper* simHandler;

int main(int argc, char** argv){

	// ----------------------------
	// DATA EXTRACTION DRIVER
	// ---------------------------
	//
	// It performs a pseudo PELE and logs all the data
	//
	// Parameters are:
	// 1-  Path of the protein
	// 2-  Number of steps
	// 3-  Temperature
	// 4-  Path of the conf file describing the ANM
	//-----------------------------


	// ----------------------------
	// Setup
	// ---------------------------
	vector<double> cutoffList;
	cutoffList.push_back(10);
	cutoffList.push_back(10);
	cutoffList.push_back(15);
	cutoffList.push_back(15);
	cutoffList.push_back(20);
	cutoffList.push_back(30);
	System sys;
	ComplexBuilder complexBuilder;
	Complex * complex = complexBuilder.build(argv[1], NB_GEN_MSCALE, cutoffList);
	Solvent* solvent = SolventGenerator::createSolvent(*complex,false);
	RandomGenerator randgen(1234);
	EnergyCalculator* enerCalc = new EnergyCalculator(OPLS,solvent);

	double* lastCoordinates; // Aqui se guardan las coordenadas antes de la perturbacion de ANM
	unsigned int coordsSize = complex->getNumberOfAllCoordinates();
	lastCoordinates = new double[coordsSize];
	double beta =  1.0/(PhysConsts::Kb_KCal * atoi(argv[3]));
	unsigned int num_iters = atoi(argv[2]);
	unsigned int num_accepted = 0;
	//----------------------------

	//----------------------------
	// Simulation objects creation
	//----------------------------
	cout<<"--- Populating objects ---"<<endl;
	PathPlanning::Tools::ANMObjectsPackage pack(&sys, complex, solvent);
	pack.populateANMObjects(argv[4]); // "src/PathPlanning/RRT/Variations/ANMRRT/ANMProteinRRT/Test/Data/anm_config.conf"
	simHandler = new ANMDataWrapper(pack);
//	simHandler->randomWeightInitialization();
	simHandler->weightInitialization(0.5);
	unsigned int number_of_modes = pack.anmParameters->getNumbermodes();
	cout<<"--- Populated ---"<<endl;
	//---------------------------


	//--------------------
	// FIRST STEP LOGGING
	//--------------------

	// System's initial elastic network energy
	SystemVars::getLog("elastic_energy")->write(toString(
						simHandler->getElasticNetworkEnergyCalculation(
								simHandler->getInitialCoordinates(),
								simHandler->getInitialCoordinates())));

	// First structure energy
	SystemVars::getLog("energy")->write(toString( enerCalc->calcEnergy(complex->getAllCartesianCoordinates(), complex->getTopology(), complex->getNBGenerator())));
	simHandler->writeVector("first_coords",simHandler->getInitialCoordinates(),76*3);

	// Random weights
	simHandler->writeVector("initial_weights",simHandler->getANMWeights(),3);

	//----------------------------
	//	PELE
	//----------------------------
	cout<<"--- Starting Iterations ---"<<endl;
	double e_new,e_old;
	e_old = 0;
	e_new = enerCalc->calcEnergy(complex->getAllCartesianCoordinates(), complex->getTopology(), complex->getNBGenerator());
	for(unsigned int i=0; i < num_iters; ++i){
		cout<<"--- Iteration "<<i<<" ---"<<endl;
		// Guardado de Coordenadas
		memcpy(lastCoordinates,complex->getAllCartesianCoordinates(),coordsSize*sizeof(double));

		// Iteración de ANM (perturbacion)
		iterate(pack, solvent);

		// Paso de aceptación
		e_new = enerCalc->calcEnergy(complex->getAllCartesianCoordinates(), complex->getTopology(), complex->getNBGenerator());

		if(accepted(e_new,e_old,randgen,beta)){
			e_old = e_new;
			num_accepted++;
			cout<<"--- Accepted ---"<<endl;


			//---------------
			// WEIGHT AND MODE PROJECTIONS SOLVING
			//---------------
			vector<double> weights = simHandler->solveWeights();
			for (unsigned int j = 0; j < number_of_modes; ++j) {
				SystemVars::getLog("weights_mode_"+toString(j))->write(toString(weights[j]));
			}
			exit(0);
			vector<double> distprojections = simHandler->calcDistanceProjections();
			for (unsigned int j = 0; j < number_of_modes; ++j) {
				SystemVars::getLog("distproj_mode_"+toString(j))->write(toString(distprojections[j]));
				SystemVars::getLog("pseudow_mode_"+toString(j))->write(toString(distprojections[j+number_of_modes]));
			}

			//--------------
			// DATA LOGGING
			//--------------
			SystemVars::getLog("elastic_energy")->write(toString(
								simHandler->getElasticNetworkEnergyCalculation(simHandler->getInitialCoordinates(),
								simHandler->getCurrentCoordinates())));

			SystemVars::getLog("energy")->write(toString(e_new));

			SystemVars::getLog("accepted")->write(toString(((double)num_accepted)/(i+1)));

			SystemVars::getLog("rmsd")->write(toString(
									simHandler->getRMSD(simHandler->getCurrentCoordinates(),simHandler->getInitialCoordinates(),simHandler->getNodesSize())
									));

			vector<double>eigenproj =  simHandler->smartCalcProjectionWithInitialEigenvectors();
			SystemVars::getLog("eigenproj_max")->write(	toString(eigenproj[0] )	);
			SystemVars::getLog("eigenproj_min")->write(	toString(eigenproj[1] )	);
			SystemVars::getLog("eigenproj_mean")->write(toString(eigenproj[2] )	);
			SystemVars::getLog("eigenproj_ok")->write(	toString(eigenproj[3] )	);

			PDBWriter::write("trajectory.pdb", *complex);
		}
		else{
			// Put again the old coordinates
			memcpy(complex->getAllCartesianCoordinates(),lastCoordinates,coordsSize*sizeof(double));
			cout<<"--- Rejected ---"<<endl;
		}
		SystemVars::getLog("accepted_total")->write(toString(((double)num_accepted)/(i+1)));
	}
	simHandler->writeVector("last_coords",simHandler->getCurrentCoordinates(),76*3);
	cout<<"--- Simulation finished ---"<<endl;

	// Complex and solvent are deleted within the pack

	delete lastCoordinates;
	delete simHandler;

	return 0;
}

void iterate(PathPlanning::Tools::ANMObjectsPackage& pack, Solvent* solvent){
	solvent->sgbUpdate(*(pack.complex));

	/*pack.anmCalculator->compute(pack.complex); 	// Se ejecuta según el eigen update frequency del conf file,
												// por lo que se puede llamar cada vez sin mayor problema.
												// Según sea el mode change frequency se llamará al picking o no.
	pack.anmCalculator->minimize(pack.anmMinParameters,pack.complex,pack.energyCalculator, pack.anmMinimizer);
	*/

	simHandler->compute();
	simHandler->writeEigenvectors_octave();
	cout<<"minimizing"<<flush<<endl;
	simHandler->minimize();
}

// copia de PELE::stepIsAccepted
bool accepted(double e_new, double e_old,RandomGenerator& randomGen, double beta){
	bool accept_move = true;

	double metropolisEnergy = e_new - e_old;

	if(metropolisEnergy > 0.)
	{
		double boltz = Math::inverseExponential(beta * metropolisEnergy); //exp(- beta * metropolisEnergy);
		double random= randomGen.getRandomDouble(0.0, 1.0);

		if(random > boltz)
		{
			accept_move = false;
		}
	}

	return accept_move;
}

