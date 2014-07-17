/////////////////////////////////////////////////////////////////////////////
/// \file ANMDataExtractor.cpp
/// \brief bla, bla
///
/// \author vgil
/// \date 02/08/2011
/////////////////////////////////////////////////////////////////////////////

#include "ANMDataWrapper.h"



ANMDataWrapper::ANMDataWrapper(PathPlanning::Tools::ANMObjectsPackage& pack) {
	this->pack = &pack;
	this->anmcalc= pack.anmCalculator;
	this->anmalg = anmcalc->getAlgorithm();
	this->anmparams = anmcalc->getParameters();
	this->eigenvectors = NULL;
	this->complex = pack.complex;
	this->atoms = pack.complex->getAllAtoms();
	this->atoms_size = pack.complex->getNumberOfAllAtoms();

	this->initial_coordinates = 	NULL;
	this->current_coordinates = 	NULL;
	this->last_coordinates = 		NULL;
	this->en_coordinates	= 		NULL;
	this->aux_coordinates	= 		NULL;

	this->initial_eigenvectors = NULL;

	anmalg->generateNodes(complex,this->nodes);

	nodesSize = nodes.size();

	save_coords(initial_coordinates);

	// Initialize memory to store the eigenvectors
	this->eigen_size = anmcalc->getParameters()->getNumbermodes()*nodesSize*3;
	initial_eigenvectors = new double[eigen_size];

	srand(time(NULL));
}

ANMDataWrapper::~ANMDataWrapper(){
	if(initial_coordinates)	delete initial_coordinates;
	if(current_coordinates)	delete current_coordinates;
	if(last_coordinates)	delete last_coordinates;
	if(en_coordinates)		delete en_coordinates;
	if(aux_coordinates)		delete aux_coordinates;
	if(initial_eigenvectors)delete initial_eigenvectors;
}

void ANMDataWrapper::randomWeightInitialization(){
	unsigned int number_of_modes = anmcalc->getParameters()->getNumbermodes();
	vector<double> final_weights;
	for (unsigned int i = 0; i < number_of_modes; ++i){
		final_weights.push_back((rand()%1000)/1000.-(rand()%1000)/1000.);
	}
	anmparams->setWeights(final_weights);

}

void ANMDataWrapper::weightInitialization(double value){
	unsigned int number_of_modes = anmcalc->getParameters()->getNumbermodes();
	vector<double> final_weights(number_of_modes, value);
	anmparams->setWeights(final_weights);
}

void ANMDataWrapper::compute(){
	if(anmcalc->compute(this->complex) == 1){
		// Save the elastic network initial coordiants (to calculate energies)
		save_coords(en_coordinates);
		// Saves the newly calculated eigenvectors
		memcpy(this->initial_eigenvectors,anmalg->getEigenvectors(),this->eigen_size*sizeof(double));
	}
}

void ANMDataWrapper::minimize(){

	save_coords(last_coordinates);
	save_coords(aux_coordinates);

	anmcalc->minimize(pack->anmMinParameters,pack->complex,pack->energyCalculator, pack->anmMinimizer);

	save_coords(current_coordinates);

	// modifica last_coordinates y current_coordinates
	Math::superposeWithSelection(complex->getNumberOfAllAtoms(),
								 complex->getAllCartesianCoordinates(),
								 anmalg->getNodeList().size(),
								 current_coordinates,
								 aux_coordinates);

	// As the current_coordinates were changed, we store them again (with the modified structure)
	save_coords(current_coordinates);
}


double ANMDataWrapper::getRMSD (double* coords_one, double* coords_two, unsigned int num_nodes){
	return Math::calcRMS(coords_one,coords_two,num_nodes);
}

///////////////////////////////////////////////////////////////
/// \remarks
///  Calculates the total energy of the elastic network.
///
/// \param en_coords Those are the coordinates in the moment that the reference
///					elastic network was constructed. This coordinates will be used
///					to check the connectivity.
///
/// \param current_coords The current coordinates of the model.
///
/// \return double The energy of a given elastic network
///
/// \author vgil
/// \date 25/07/2011
///////////////////////////////////////////////////////////////
double ANMDataWrapper::getElasticNetworkEnergyCalculation(double* en_coords, double* current_coords){

	double val = 0;
	double dis2 =0;
	double cutoff_dist2 =0;
	bool in_same_chain = false;
	double force_constant;

	vector<Point> elastic_network_points;
	vector<Point> current_points;
	from_coords_to_points(en_coords,nodesSize,elastic_network_points);
	from_coords_to_points(current_coords,nodesSize,current_points);

	double cutoff = pack->anmParameters->getCutoff();
	double cutoff2 = cutoff*cutoff;

	for(unsigned int i=0;i<nodesSize;++i){
		for(unsigned int j=i+1;j<nodesSize;++j){

			cutoff_dist2 = elastic_network_points[i].sqDistance(elastic_network_points[j]);
			dis2 = current_points[i].sqDistance(current_points[j]);

			if(dis2 < cutoff2){

				// Si están consecutivos...
				in_same_chain = (atoms[this->nodes[i]]->residue->getNextLink() == atoms[this->nodes[j]]->residue->getNextLink());

				if(in_same_chain){
					force_constant = pack->anmParameters->getBondedConstantForHessian()/dis2;
				}
				else{
					force_constant = pack->anmParameters->getConstantForHessian()/pow(dis2,pack->anmParameters->getSpringConstantDecay());
				}

				// 1/2 dr*dr * K, al calcular solo el triangulo superior no hace falta multiplicar
				val+=dis2*force_constant;
			}
		}
	}
	return val;
}

void ANMDataWrapper::from_coords_to_points(double* coords, unsigned int size, vector<Point>& points){
	points.clear();
	for (unsigned int i = 0; i < size; ++i) {
		points.push_back(Point(&(coords[i*3])));
	}
}

void ANMDataWrapper::writeEigenvectors_octave (){
	vector<vector<double> >  eig;
	anmcalc->getEigenvectors(eig);


		string line = "[";
		for (unsigned int i = 0; i < eig.size(); ++i){
			for (unsigned int j = 0; j < eig[i].size(); ++j){
				line+=toString(eig[i][j])+((j!=eig[i].size()-1)?",":"");
			}
			line+=((i!=eig.size()-1)?";":"");
		}
		line += "]";
		SystemVars::getLog("ANM_eigenvectors")->write(line);
}

void ANMDataWrapper::save_coords(double*& here){

	if(!here) here = new double[nodesSize*3];

	for(unsigned int i = 0; i < nodesSize; ++i){
		Point p = atoms[nodes[i]]->toPoint();
		here[i*3] = p.getX();
		here[i*3+1] = p.getY();
		here[i*3+2] = p.getZ();
	}
}


vector<double> ANMDataWrapper::solveWeights(){
	vector<double> weights;
	vector<int>& node_list_eigen 	= 	anmalg->getNodeList();
	unsigned int nodes_size 		= 	node_list_eigen.size();
	unsigned int dimension 			= 		3;
	unsigned int number_of_modes 	= 	pack->anmParameters->getNumbermodes();
	unsigned int mode_size			= 		nodes_size*dimension;

	// Distances vector
	double distances[mode_size];
	for(unsigned int i = 0; i < mode_size; ++i){
		distances[i] = 	current_coordinates[i] - last_coordinates[i];
	}

	writeEigenvectors_octave();

	writeVector_octave("distances",distances,mode_size);

	// Deduce weights
	Solver s(number_of_modes,mode_size);

	s.setDistModificator(anmcalc->getParameters()->getDisplacementFactor()*anmcalc->getAlgorithm()->getInvBiggestNorm());
	SystemVars::getLog("dist_modif")->write(toString(anmcalc->getParameters()->getDisplacementFactor()*anmcalc->getAlgorithm()->getInvBiggestNorm()));


	s.setDistances(distances,mode_size);
	s.setEigenVectors(anmalg->getEigenvectors(), mode_size*number_of_modes, true);
	s.setHigherRange(20);
	s.setLowerRange(-20);
	s.solve();

	double* w = s.getWeights();
	for(unsigned int i =0; i < number_of_modes; ++i){
		weights.push_back(w[i]);
	}

	return weights;
}

vector<double> ANMDataWrapper::calcDistanceProjections	(){

	vector<double> p;
	vector<double> pw;
	vector<double> pwp;

	vector<int>& node_list_eigen 	= 	anmalg->getNodeList();
	unsigned int nodes_size 		= 	node_list_eigen.size();
	unsigned int dimension 			= 		3;
	unsigned int number_of_modes 	= 	pack->anmParameters->getNumbermodes();
	unsigned int mode_size			= 		nodes_size*dimension;


	// Distances vector
	double distances[mode_size];
	for(unsigned int i = 0; i < mode_size; ++i){
		distances[i] = 	current_coordinates[i] - last_coordinates[i];
	}

	// Solving
	Solver s(number_of_modes,mode_size);
	s.setDistances(distances,mode_size);
	s.setEigenVectors(anmalg->getEigenvectors(), mode_size*number_of_modes, true);
	s.setHigherRange(20);
	s.setLowerRange(-20);
	s.solveProjections(p,pw,pwp);

	return p;
}

void ANMDataWrapper::writePoints(string file, vector<Point>& points){
	for(unsigned int i =0; i < points.size();++i){
		SystemVars::getLog(file)->write(points[i].toString());
	}
}

void ANMDataWrapper::writeVector(string file, double* vec, unsigned int vec_size){
	vector<Point> points;
	points.clear();
	for (unsigned int i = 0; i < vec_size/3; ++i){
		points.push_back(Point(&(vec[i*3])));
	}

	for(unsigned int i =0; i< points.size();++i){
		SystemVars::getLog(file)->write(points[i].toString());
	}
}

void ANMDataWrapper::writeVector_octave(string file, double* vec, unsigned int vec_size){
	string line2 = "[";
	for(unsigned int i = 0; i < vec_size; ++i){
		line2+=toString(vec[i])+",";
	}
	line2+="]";
	SystemVars::getLog(file)->write(line2);
}


double* ANMDataWrapper::getInitialCoordinates(){
	return initial_coordinates;
}

double* ANMDataWrapper::getCurrentCoordinates(){
	return current_coordinates;
}

double* ANMDataWrapper::getLastCoordinates(){
	return last_coordinates;
}

double*	ANMDataWrapper::getElNetworkInitialCoords(){
	return en_coordinates;
}

double*	ANMDataWrapper::getANMWeights(){
	return &(anmparams->getWeights()[0]);
}


unsigned int ANMDataWrapper::getNodesSize(){
	return anmalg->getNodeList().size();
}

double ANMDataWrapper::calcProjectionWithInitialEigenvectors(){
	unsigned int number_of_modes = anmcalc->getParameters()->getNumbermodes();
	anmcalc->compute(this->complex);
	return calc_projections(anmalg->getEigenvectors(),initial_eigenvectors,nodesSize*3,number_of_modes);
}

double 	ANMDataWrapper::calc_projections(double* v1, double* v2,unsigned int v12size,unsigned int num_of_vectors){
	unsigned int offset = 0;
	double accum = 0;
	for(unsigned int i =0; i < num_of_vectors; ++i){
		double* av1 = v1+offset;
		double* av2 = v2+offset;
		double norm1 = Math::ourDnrm2(v12size, av1);
		double norm2 = Math::ourDnrm2(v12size, av2);
		accum += Math::dotProduct(v12size,av1,av2)/(norm1*norm2);
		offset+=v12size;
	}

	return accum / num_of_vectors;
}

vector<double>	ANMDataWrapper::smartCalcProjectionWithInitialEigenvectors(){
	unsigned int number_of_modes = anmcalc->getParameters()->getNumbermodes();
	anmcalc->compute(this->complex);
	unsigned int mode_size = nodesSize*3;

	return calc_smart_projections(anmalg->getEigenvectors(),initial_eigenvectors,mode_size,number_of_modes);
}


// Calcula las relaciones, pero puede fallar. Hacer un algoritmo que cubra todos los casos daría M! casos,
// donde M es el número de modos. Este sólo da la solución naive si existe (en el caso de no existir las diferencias
// deberían ser demasiado grandes).
vector<double> 	ANMDataWrapper::calc_smart_projections (double* v1, double* v2,unsigned int v12size,unsigned int num_of_vectors){
		bool used[num_of_vectors];

		vector<double> projections;
		vector<double> results;
		double mean = 0;
		int relationship[num_of_vectors];
		for (unsigned int j = 0; j < num_of_vectors; ++j) relationship[j] = -1;

		for (unsigned int i = 0; i < num_of_vectors; ++i){

			unsigned int related;

			double p = calc_one_smart_projection(v1+(i*v12size),v2,v12size,num_of_vectors,&related);

			mean+=p;
			projections.push_back(p);
			relationship[i] = related;
		}

		mean /= num_of_vectors;

		results.push_back(*(std::max_element(projections.begin(),projections.end())));
		results.push_back(*(std::min_element(projections.begin(),projections.end())));
		results.push_back(mean);

		// Check if a 1 to 1 relationship was established
		results.push_back((double) false);
		for (unsigned int j = 0; j < num_of_vectors; ++j) used[j] = false;

		for (unsigned int i = 0; i < num_of_vectors; ++i) {
			if(relationship[i] == -1 || used[i]){
				results[3] = true;
				used[i] = true;
			}
		}

		if(results[3] == true){
			cout<<"Impossible to establish relationship. "<<endl;
		}


		// Print relationship
		for (unsigned int j = 0; j < num_of_vectors; ++j){
			cout<< "("<<j<<", "<<relationship[j]<<")"<<endl;
		}

		return results;
}

// v1 vs all in v2 which are free
double ANMDataWrapper::calc_one_smart_projection (double* v1, double*v2, unsigned int v12size,unsigned int num_of_vectors, unsigned int* related){
	vector<double> p;
	unsigned int offset = 0;
	double cosinus = 0;
	double norm1 = Math::ourDnrm2(v12size, v1);
	double maxcosinus = 0;
	unsigned int maxi = -1;

	for(unsigned int i = 0; i < num_of_vectors; ++i){
		double* av2 = v2+offset;

		double norm2 = Math::ourDnrm2(v12size, av2);
		cosinus = Math::dotProduct(v12size,v1,av2)/(norm1*norm2);

		if(fabs(cosinus) > maxcosinus){
			maxcosinus = fabs(cosinus);
			maxi = i;
		}

		offset+=v12size;
	}

	*related = maxi;
	return maxcosinus;
}

