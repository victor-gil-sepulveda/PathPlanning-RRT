/*
 * ANMProteinRRTExpansionAlgorithm.cpp
 *
 *  Created on: 12/06/2011
 *      Author: vgil
 */

#include "ANMProteinRRTExpansionAlgorithm.h"





ANMProteinRRTExpansionAlgorithm::ANMProteinRRTExpansionAlgorithm(PathPlanning::Tools::ANMObjectsPackage* pack, Solver* s)
								:RRTProteinExpansionAlgorithm(NULL){
	set_ANM_calculator		(pack->anmCalculator);
	set_energy_calculator	(pack->energyCalculator);
	set_minimization_params	(pack->anmMinParameters);
	set_minimizer			(pack->anmMinimizer);

	set_solver				(s);
}

ANMProteinRRTExpansionAlgorithm::~ANMProteinRRTExpansionAlgorithm(){}

ANMCalculator* ANMProteinRRTExpansionAlgorithm::getANMCalculator(){
	return this->anmcalc;
}

void ANMProteinRRTExpansionAlgorithm::set_ANM_calculator(ANMCalculator* anmc){
	this->anmcalc = anmc;
}

Solver *ANMProteinRRTExpansionAlgorithm::getSolver() const{
    return solver;
}


RRTNode* ANMProteinRRTExpansionAlgorithm::do_expansion(RRTNode* from, RRTNode* to){

	ANMProteinConfiguration* from_conf = dynamic_cast<ANMProteinConfiguration*>(from->getData());
	ANMProteinConfiguration* to_conf = dynamic_cast<ANMProteinConfiguration*>(to->getData());
	AtomSet* protein = from_conf->getProtein();

	//---------------------------------
	// Save coordinates before the expansion
	//---------------------------------
	vector<Point> old_points;
	//--
	// Será un poco duro generalizar esto..
	vector<Atom*> c_alphas = protein->getAtomsWithName(AtomNames::CA);
	unsigned int c_alphas_size = c_alphas.size();
	//--
	for(unsigned int i =0; i < c_alphas.size();++i){
		old_points.push_back(c_alphas[i]->toPoint());
	}
	//--------------------------------


	//---------------------------------
	// And move the system in the direction pointed by the combination of normal modes and
	// weights
	//---------------------------------
	// Set new weights
	anmcalc->getParameters()->setWeights(to_conf->getWeights());
	// Calculate directions and target points
	anmcalc->getAlgorithm()->pickAndUpdate();
	// Apply constrainst and minimize
	anmcalc->minimize(minim_parameters, protein, energy_calculator, minimizer);
	//----------------------------------

	//----------------------------------
	// We need to calculate the distances between atoms for each coordinate component
	//----------------------------------
	vector<Point> new_points;
	for(unsigned int i =0; i < c_alphas.size();++i){
		new_points.push_back(c_alphas[i]->toPoint());
	}

	unsigned int mode_size = c_alphas_size*3;
	double node_coord_displacements[mode_size];
	for(unsigned int i =0; i < new_points.size(); ++i){
		node_coord_displacements[i*3] = new_points[i].getX()-old_points[i].getX();
		node_coord_displacements[i*3+1] = new_points[i].getY()-old_points[i].getY();
		node_coord_displacements[i*3+2] = new_points[i].getZ()-old_points[i].getZ();
	}
	//----------------------------------

	//----------------------------------
	// Now calculate the real expansion in terms of amplitude, which  means solving an
	// Ax = b system, where A are the eigenvectors and b are the displacements.
	// First we need to set up the solver.
	//----------------------------------
	// We set the initial guess (the weights we have used to calculate the target points)
	solver->setWeights(to_conf->getWeights());
	// Now we set the upper and lower limits for the result (from the starting connfiguration)
	solver->setHigherRange(from_conf->getUpperBound(),anmcalc->getParameters()->getNumbermodes());
	solver->setLowerRange(from_conf->getLowerBound(),anmcalc->getParameters()->getNumbermodes());
	// Then set the distances...
	solver->setDistances(node_coord_displacements,c_alphas.size()*3);
	// ... and the modes
	// TODO: solver tiene que compartir los modos para no estresar a la memoria
	solver->setEigenVectors(anmcalc->getEigenvectors(),c_alphas_size*3*anmcalc->getParameters()->getNumbermodes(),true);
	// Get the distance modification factor from the ANM calculation
	cout<<"df "<<anmcalc->getAlgorithm()->getDisplacementFactor()<<" nf"<<anmcalc->getAlgorithm()->getNormalizationFactor()<<endl;
	cout<<"mod fact"<<(1/anmcalc->getAlgorithm()->getNormalizationFactor())/anmcalc->getAlgorithm()->getDisplacementFactor()<<endl;

	solver->setDistModificator(anmcalc->getAlgorithm()->getDisplacementFactor()/anmcalc->getAlgorithm()->getNormalizationFactor());
	// Finally we calculate the 'real' weights after minimization
	solver->solve();
	//----------------------------------

	//---------------------------------
	// Generate the new configuration and return the new node
	//---------------------------------
	double* new_weights = solver->getWeights();
	vector<double> new_v_weights(new_weights, new_weights + solver->getTotalModes());
	ANMProteinConfiguration* new_conf = new ANMProteinConfiguration(protein, anmcalc,from_conf->getBoundaries(),new_v_weights);
	RRTNode* node = new RRTNode;
	node->setDataP(dynamic_cast<RRTConfiguration*>(new_conf));

	return node;
	//-----------------------------------
}

EnergyCalculator *ANMProteinRRTExpansionAlgorithm::getEnergyCalculator() const{
    return energy_calculator;
}

MinParams *ANMProteinRRTExpansionAlgorithm::getMinimParameters() const{
    return minim_parameters;
}


void ANMProteinRRTExpansionAlgorithm::set_energy_calculator(EnergyCalculator *energyCalculator){
    this->energy_calculator = energyCalculator;
}

void ANMProteinRRTExpansionAlgorithm::set_minimization_params(MinParams *minimParameters){
    this->minim_parameters = minimParameters;
}

void ANMProteinRRTExpansionAlgorithm::set_minimizer(Minimizer *minimizer){
    this->minimizer = minimizer;
}

void ANMProteinRRTExpansionAlgorithm::set_solver(Solver* solver){
    this->solver = solver;
}




