#include "TestASA_CG.h"

/*-----------------------------------------------------------
Function: TestASA_CG::TestASA_CG()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestASA_CG::TestASA_CG(){
	Test::create("");
}

/*-----------------------------------------------------------
Function: TestASA_CG::TestASA_CG(string name)

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestASA_CG::TestASA_CG(string name){
	test_name = name;
}


/*-----------------------------------------------------------
Function: TestASA_CG:~TestASA_CG()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestASA_CG::~TestASA_CG(){
}

/*-----------------------------------------------------------
Function:void TestASA_CG::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestASA_CG::init(){
}

namespace testASAvals{

	int a_dim_col = 3;
	int a_dim_row = 3;

	// 3x3
	double Atmp[]={1, 3,-2,
				3, 5, 6,
				2, 4, 3};

	double AT[]={1, 3,2,
				 3, 5, 4,
				 -2,6, 3};

	// A = ATA
	double A[]={14, 26, 22,
				26, 50, 36,
				22, 36, 49};

	// 1x3
	double btmp[] ={5,7,8};

	// b = ATb
	double b[] ={42, 82, 56};

};

using namespace testASAvals;
using Json::Value;


bool TestASA_CG::test_minimath_1(){
	double A[]={1,2};

	double B[]={1,2,
				3,4};

	double C[2];

	Math::Matrix::matrixMult(A,B,C,1,2,2,2);

	cout<<C[0]<<" "<<C[1]<<endl;

	return C[0]==7 && C[1]==10;
}

bool TestASA_CG::test_minimath_2(){
	double A[]={1,2,
				3,4};

	double B[]={1,2,
				3,4};

	double C[4];

	Math::Matrix::matrixMult(A,B,C,2,2,2,2);

	cout<<C[0]<<" "<<C[1]<<endl;
	cout<<C[2]<<" "<<C[3]<<endl;

	return C[0]==7 && C[1]==10 && C[2]==15 && C[3]==22;
}

bool TestASA_CG::test_minimath_3(){
	double A[]={1,2,
				3,4};

	double B[]={1,2,3,
				4,5,6};

	double C[6];

	Math::Matrix::matrixMult(A,B,C,2,2,2,3);

	cout<<C[0]<<" "<<C[1]<<" "<<C[2]<<endl;
	cout<<C[3]<<" "<<C[4]<<" "<<C[5]<<endl;

	return C[0]==9 && C[1]==12 && C[2]==15 && C[3]==19 && C[4]==26 && C[5]==33;
}

bool TestASA_CG::test_minimath_4(){
	double B[]={1,2,3,
				4,5,6};

	double BT[6];

	double BTexp[]={1,4,
					2,5,
					3,6};

	Math::Matrix::transpose(B,BT,3,2);

	double ATcalc[9];
	Math::Matrix::transpose(Atmp,ATcalc,3,3);

	return Assertion::assertExpectedVectorEqualsCalculatedVectorWithinPrecision(AT,ATcalc,9,1e-3) &&
		   Assertion::assertExpectedVectorEqualsCalculatedVectorWithinPrecision(BT,BTexp,6,1e-3);
}

namespace testASAFunctions{
	// Para que funcione se tiene que resolver con un A positivo definido y simétrico, por lo
	// que podemos resolver para ATAx=ATb (o lo que es lo mismo, en primera instancia transformar
	// A en ATA y b en ATb

	double myvalue(asa_objective *asa){
		unsigned int n = asa->n;
		double* x = asa->x;

		double bTx = Math::dotProduct(3,b,x);
		double Ax[n];

		Math::Matrix::matrixMult(A,x,Ax,3,3,3,1);
		double xTAx = Math::dotProduct(3,x,Ax);

		return 0.5*xTAx - bTx;
	}

	void mygrad(asa_objective *asa){
		double* x = asa->x;
		double* g = asa->g;
		unsigned int n = asa->n ;

		double Ax[n];
		Math::Matrix::matrixMult(A,x,Ax,3,3,3,1);

		// Substract b from Ax (Ax-b)
		for(unsigned int i = 0;i<n;++i)
			g[i]=Ax[i]-b[i];
	}

	double myvalgrad (asa_objective *asa){
		double* g = asa->g;
		double* x = asa->x;
		unsigned int n = asa->n;

		double bTx = Math::dotProduct(3,b,x);
		double Ax[n];

		Math::Matrix::matrixMult(A,x,Ax,3,3,3,1);
		double xTAx = Math::dotProduct(3,x,Ax);

		// Substract b from Ax (Ax-b)
		for(unsigned int i = 0;i<n;++i)
			g[i]=Ax[i]-b[i];

		return 0.5*xTAx - bTx;
	}
};

using namespace testASAFunctions;


//-----------------
// Resolucion del sistema :
//  x + 3y - 2z = 5
// 3x + 5y + 6z = 7
// 2x + 4y + 3z = 8
// Resultado:
// [x = -15, y = 8, z =  2]
// hecho a partir de driver1.c
bool TestASA_CG::test_solving(){

	asacg_parm cgParm;
	asa_parm asaParm;

	double expected[] = {-15,8,2} ;

	unsigned int n = 3 ;
	double* lo = (double *) malloc (n*sizeof (double)) ;
	double* hi = (double *) malloc (n*sizeof (double)) ;
	for (unsigned int i = 0; i < n; i++) lo [i] = -50 ;
	for (unsigned int i = 0; i < n; i++) hi [i] = 50 ;

	double* x  = (double *) malloc (n*sizeof (double)) ;
	for (unsigned int i = 0; i < n; i++) x [i] = 0 ;

	asa_cg_default(&cgParm);
    asa_default(&asaParm);

    cout<<"Return code: "<<asa_cg(x, lo, hi, n, NULL, &cgParm, &asaParm, 1.e-8, myvalue, mygrad, NULL, NULL,NULL)<<endl;

    cout<< "Result: ";
    for(unsigned int i = 0; i < n; i++){
    	cout<<x[i]<<" ";
    }
    cout<<endl;

    free (lo);
    free (hi);

    bool result =  Assertion::assertExpectedVectorEqualsCalculatedVectorWithinPrecision(expected,x,3,1.e-2);
    free(x);

    return result;
}

/* -----------------------------------------------------------
Function: void TestASA_CG::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestASA_CG::run(){
	Test::run();
	//----------------------------------------------------

	TEST_FUNCTION(test_solving);
	TEST_FUNCTION(test_minimath_1);
	TEST_FUNCTION(test_minimath_2);
	TEST_FUNCTION(test_minimath_3);
	TEST_FUNCTION(test_minimath_4);


	//-----------------------------------------------------
	finish();
}

/* -----------------------------------------------------------
Function: void TestASA_CG::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestASA_CG::finish(){

	//-----------------------------------------------------

	//-----------------------------------------------------
	Test::finish();
}


