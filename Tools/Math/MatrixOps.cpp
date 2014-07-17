/*
 * MatrixOps.cpp
 *
 *  Created on: 21/06/2011
 *      Author: victor
 */

#include "MatrixOps.h"


namespace Math{
	namespace Matrix{

		bool matrixMult(double* A, double* B, double* C, unsigned int A_col_size,unsigned int A_row_size,unsigned int B_col_size, unsigned int B_row_size){

			// The row size of A has to be equal to the colum size of B
			if(A_row_size!=B_col_size){
				cout<<"Impossible to do the multiplication."<<endl;
				return false;
			}


			// If so, we do the multiplication
			// The resultant matrix has rows of the same size as B and colums of the same size as A

			// We are going to store each column of B here
			double 	tmp_B_col[B_col_size];

			for(unsigned int i = 0; i < B_row_size;++i){

				for(unsigned int j = 0; j < B_col_size;++j){
					tmp_B_col[j]=B[i+(j*B_row_size)];
				}


				// Now multiply all the rows of A with the column B, this will form the ith
				// row of C
				// And now get all the values via dot product
				for(unsigned int j = 0; j < A_col_size; ++j){
					C[j*B_row_size+i] = dotProduct(B_col_size,&(A[j*A_row_size]),tmp_B_col);
				}
			}

			return true;
		}

		bool transpose (double* A, double* AT,unsigned int A_row_size, unsigned int A_column_size){
			for(unsigned int i = 0; i< A_row_size; ++i){
				for (unsigned int j = 0; j < A_column_size; ++j) {
					AT[j+i*A_column_size] = A[i+j*A_row_size];
				}
			}

			return true;
		}
	}
}
