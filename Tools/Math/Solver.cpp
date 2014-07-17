/*
 * Solver.cpp
 *
 *  Created on: 22/06/2011
 *      Author: victor
 */

#include "Solver.h"



Solver::Solver(unsigned int totalModes,unsigned int modeSize) {

	eig_modified = 	true;
	dist_modified = true;

	number_of_modes =	totalModes;
	mode_size 	= 		modeSize;
	eig 		=		NULL;
	weights 	= 		NULL;
	distances 	=	 	NULL;
	minvalues 	= 		NULL;
	maxvalues 	= 		NULL;
	dist_modificator =  1;

	// Working vectors
	objective.A = (double*) malloc(number_of_modes*number_of_modes* sizeof(double)); // A is a square matrix (because is AT*A)
	objective.b = (double*) malloc(mode_size*sizeof(double));
	eigT = (double*) malloc(number_of_modes * mode_size * sizeof(double));
}

Solver::~Solver() {
	if(eig!=NULL)		free(eig);
	if(weights!=NULL)			free(weights);
	if(distances!=NULL)			free(distances);
	if(objective.A!=NULL)		free(objective.A);
	if(objective.b!=NULL)		free(objective.b);
	if(maxvalues!=NULL)			free(maxvalues);
	if(minvalues!=NULL)			free(minvalues);
	if(eigT!=NULL)				free(eigT);
}

void Solver::solve(double grad_tol){
	if(eig){
		if(eig_modified || dist_modified){

			// If we have modified the eigenvalues from the last run, we have to recreate the
			// symmetric positive-definite matrix to use with the conjugated gradient.
			if(eig_modified){

//			cout<<"Eigenvectors---"<<endl;
//			for (unsigned int i = 0; i < mode_size;++i){
//				for (unsigned int j = 0; j < total_modes;++j){
//					cout<<eigenvectors[i*total_modes+j]<<" ";
//				}
//				cout<<endl;
//			}
//			cout<<endl;
//			cout<<"Transposed---"<<endl;
//			for (unsigned int i = 0; i < total_modes;++i){
//				for (unsigned int j = 0; j < mode_size;++j){
//					cout<<eigT[i*mode_size+j]<<" ";
//				}
//				cout<<endl;
//			}
//			cout<<endl;

				Math::Matrix::matrixMult(eigT,eig,objective.A,number_of_modes,mode_size,mode_size,number_of_modes);

//			cout<<"ATA---"<<endl;
//			for (unsigned int i =0; i < total_modes;++i){
//				for (unsigned int j =0; j < total_modes;++j){
//					cout<<objective.A[i*total_modes+j]<<" ";
//				}
//				cout<<endl;
//			}
//			cout<<endl;

				eig_modified = false;
			}

			// Same for distances (as we multiply A per AT, the same has to be done for dists, so we have
			// to multiply it by 'eigenvectors' which is the transposed matrix )

			// Apply the atenuation
//		cout<<"distances before--------"<<endl;
//		for (unsigned int i = 0; i < mode_size; ++i){
//			cout<<this->distances[i]<<endl;
//		}
//
//		cout<<"Modificator--------"<<endl;
//		cout<<this->dist_modificator<<endl;

			Math::multiplyVectorByScalar(this->distances,this->dist_modificator,mode_size);

//		cout<<"distances after--------"<<endl;
//		for (unsigned int i = 0; i < mode_size; ++i){
//			cout<<this->distances[i]<<endl;
//		}

			// b = eigT*b  (eig*b in this case, as eig is already transposed)
			Math::Matrix::matrixMult(eigT,distances,objective.b,number_of_modes,mode_size,mode_size,1);
			dist_modified = false;

//		cout<<"ATb---"<<endl;
//		for (unsigned int i =0; i < total_modes;++i){
//			cout<<objective.b[i]<<" ";
//		}
//		cout<<endl;
		}

		// If the weights hasn't been initialized, they're created and initialized to 0
		if(weights==NULL){
			weights = (double*) calloc(number_of_modes, sizeof(double));
		}


		asacg_parm cgParm;
		asa_parm asaParm;
		asa_cg_default(&cgParm);
		asa_default(&asaParm);

		asa_cg(	weights, minvalues,
				maxvalues, number_of_modes,
				NULL, &cgParm, &asaParm, grad_tol,
				SolverFunctions::function_value,
				SolverFunctions::function_grad,
				SolverFunctions::function_valgrad,
				NULL, &objective);
	}
	else{
		cout<<"[WARNING Solver::solveProjections] The eigenvectors were not defined yet."<<endl;
	}
}


/*
 Hace la solución geométrica de las proyecciones/peso y de los pseudopesos (w_i = d.m_i / |m_i|)
 Para el pseudopeso dividimos por la norma de la DISTANCIA de modo que conseguimos
*/
void Solver::solveProjections(vector<double>& p,vector<double>& pw,vector<double>& pwp){

	if(eig!= NULL){
		p.clear();
		pw.clear();
		pwp.clear();

		double distnorm = Math::ourDnrm2(mode_size,distances);

		for(unsigned int i=0; i<number_of_modes; ++i){
			double* eig_vector = eigT+(mode_size*i);
			p.push_back(Math::dotProduct(mode_size,eig_vector,distances));
			pw.push_back(p[i]/distnorm);
			pwp.push_back(p[i]/Math::ourDnrm2(mode_size,eig_vector));
		}
	}
	else{
		cout<<"[WARNING Solver::solveProjections] The eigenvectors were not defined yet."<<endl;
	}
}

unsigned int Solver::getModeSize() const{
    return mode_size;
}

unsigned int Solver::getTotalModes	() const{
	return number_of_modes;
}

double* Solver::getEigenvectors() const{
    return eig;
}

double* Solver::getWeights() const{
    return weights;
}

double* Solver::getDistances() const{
    return distances;
}

double* Solver::getLowerRange() const{
	return minvalues;
}

double* Solver::getHigherRange() const{
	return maxvalues;
}

bool Solver::initialize_copy(const char* error_message, double*& local_vector, unsigned int size, unsigned int expected_size){
	if(size!= expected_size){
		cout<<"<Error "<<error_message<<" > Either the size of the call or the parameter in the Solver class are not correct ( size:"<<size<<", expected:"<<expected_size<<")."<<flush<<endl;
		return false;
	}

	if(local_vector != NULL){
		free(local_vector);
	}

	local_vector = (double*) malloc(size* sizeof(double));

	return true;
}

void Solver::set_c_array(const char* error_message, double*& local_vector, double* extern_vector,unsigned int size, unsigned int expected_size){
	if(initialize_copy(error_message,local_vector,size,expected_size)){
		memcpy(local_vector,extern_vector,size*sizeof(double));
	}
}


void Solver::set_cpp_vector(const char* error_message, double*& local_vector, vector<double>& extern_vector,unsigned int size, unsigned int expected_size){
	if(initialize_copy(error_message,local_vector,size,expected_size)){
		for(unsigned int i = 0; i < size; ++i){
			local_vector[i] = extern_vector[i];
		}
	}
}

void Solver::setDistances(double *dist, unsigned int size){
	set_c_array("Solver::setDistances(double*)",this->distances,dist,size,this->mode_size);
	dist_modified = true;
}

void Solver::setWeights(double* we, unsigned int size){
	set_c_array("Solver::setWeights(double*)",this->weights,we,size,this->mode_size);
}

void Solver::setHigherRange(double *hr, unsigned int size){
	set_c_array("Solver::setHigherRange(double*)",this->maxvalues,hr,size,this->number_of_modes);
}

void Solver::setHigherRange(double hr){
	vector<double> high(number_of_modes,hr);
	set_cpp_vector("Solver::setHigherRange(double)",this->maxvalues,high,high.size(),this->number_of_modes);

}

void Solver::setLowerRange(double *lr, unsigned int size){
	set_c_array("Solver::setLowerRange(double*)",this->minvalues,lr,size,this->number_of_modes);
}

void Solver::setLowerRange(double lr){
	vector<double> low(number_of_modes,lr);
	set_cpp_vector("Solver::setLowerRange(double)",this->minvalues,low,low.size(),this->number_of_modes);

}

void Solver::setEigenVectors(double *eigenv,unsigned int size, bool transpose){
	set_c_array("Solver::setEigenvectors(double*)",this->eig,eigenv,size,this->number_of_modes * this->mode_size);

	if(transpose){
		Math::Matrix::transpose(eig,eigT,mode_size,number_of_modes);
		std::swap(eig,eigT);
	}
	else{
		Math::Matrix::transpose(eig,eigT,number_of_modes,mode_size);
	}

	eig_modified = true;
}

void Solver::setWeights(vector<double> & we){
	set_cpp_vector("Error Solver::setWeights(vector)",this->weights, we, we.size(), number_of_modes);
}

void Solver::setDistances(vector<double> & dists){
	set_cpp_vector("Error Solver::setDistances(vector)",this->distances, dists, dists.size(), mode_size);
	dist_modified = true;
}

void Solver::setEigenvectors(vector< vector<double> >& eigenv, bool transpose){
	vector<double> eigen_temp;
	if(eigenv.size() > 0){
		unsigned int size = eigenv.size();
		unsigned int subsize = eigenv[0].size();
		for (unsigned int i = 0; i < size; ++i){
			for (unsigned int j = 0; j < subsize; ++j){
				eigen_temp.push_back(eigenv[i][j]);
			}
		}
	}

	set_cpp_vector("Error Solver::setEigenvectors(vector)",this->eig, eigen_temp, eigen_temp.size(), mode_size*number_of_modes);

	if(transpose){
		Math::Matrix::transpose(eig,eigT,mode_size,number_of_modes);
		std::swap(eig,eigT);
	}
	else{
		Math::Matrix::transpose(eig,eigT,number_of_modes,mode_size);
	}

	eig_modified = true;
}


double Solver::getDistModificator() const{
    return dist_modificator;
}

void Solver::setDistModificator(double dist_modificator){
    this->dist_modificator = dist_modificator;
}


//--------------------------------------------
// Functions for solving
//--------------------------------------------

double SolverFunctions::function_value(asa_objective *asa){
	unsigned int n = asa->n;

	double* x = asa->x;
	double* A = asa->A;
	double* b = asa->b;

	double bTx = Math::dotProduct(n,b,x);
	double Ax[n];

	Math::Matrix::matrixMult(A,x,Ax,n,n,n,1);
	double xTAx = Math::dotProduct(n,x,Ax);

//	cout<<"xTAx :"<<xTAx<<endl;
//	cout<<"Returns (value): "<<0.5*xTAx - bTx<<endl;
	return 0.5*xTAx - bTx;
}

void SolverFunctions::function_grad(asa_objective *asa){
	double* x = asa->x;
	double* g = asa->g;
	double* A = asa->A;
	double* b = asa->b;
	unsigned int n = asa->n ;
	double Ax[n];
	Math::Matrix::matrixMult(A,x,Ax,n,n,n,1);

	// Substract b from Ax (Ax-b)
	for(unsigned int i = 0;i<n;++i){
		g[i]=Ax[i]-b[i];
	}
}

double SolverFunctions::function_valgrad(asa_objective *asa){
	double* g = asa->g;
	double* x = asa->x;
	double* A = asa->A;
	double* b = asa->b;
	unsigned int n = asa->n;

	double bTx = Math::dotProduct(n,b,x);
	double Ax[n];

	Math::Matrix::matrixMult(A,x,Ax,n,n,n,1);
	double xTAx = Math::dotProduct(n,x,Ax);

	// Substract b from Ax (Ax-b)
	for(unsigned int i = 0;i<n;++i)
		g[i]=Ax[i]-b[i];

//	cout<<"xTAx :"<<xTAx<<endl;
//	cout<<"bTx :"<<bTx<<endl;
//	cout<<"Returns (valgrad): "<<0.5*xTAx - bTx<<endl;
	return 0.5*xTAx - bTx;
}
