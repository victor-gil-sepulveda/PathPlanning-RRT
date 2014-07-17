/*
 * TestRTTBase.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: vgil
 */

#include "TestRTTBase.h"


/*-----------------------------------------------------------
Function: TestRTTBase::TestRTTBase()

Description:
Constructor. Just changes the name of the test suite.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestRTTBase::TestRTTBase(){
	Test::create("");
}

/* -----------------------------------------------------------
Function: TestRTTBase::TestRTTBase(string name)

Description:
Initializes the test class giving it a name.

In:
void

Out:
void
-----------------------------------------------------------------*/

TestRTTBase::TestRTTBase(string name){
	Test::create(name);
}

/*-----------------------------------------------------------
Function: TestRTTBase:~TestRTTBase()

Description:
Destructor. Does nothing.
In:
void

Out:
void
-----------------------------------------------------------------*/
TestRTTBase::~TestRTTBase(){

}

/*-----------------------------------------------------------
Function:void TestRTTBase::init()

Description:
In this function global data has to be initialized (memory allocation, file reading... etc).

In:
void

Out:
void
-----------------------------------------------------------------*/

void TestRTTBase::init(){

	// Initialize vars we are going to use globally
}


void mysleep (unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


bool TestRTTBase::test_timer(){

	TIMER_CREATE(my_timer);

	TIMER_MEASURE(my_timer, for(int i = 0; i < 200; i++){mysleep(1);});

	TIMER_REPORT(my_timer);



	time_t start = time(NULL);
	for(int i = 0; i < 200; i++){mysleep(1);}
	time_t end = time(NULL);
	cout<<"difftime: "<<difftime(start,end)<<endl;

	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	unsigned long int  start_ = (unsigned long int)ts.tv_sec * 1000LL + (unsigned long int)ts.tv_nsec / 1000000LL;

	for(int i = 0; i < 200000000; i++){}
	clock_gettime(CLOCK_REALTIME, &ts);
	unsigned long int end_ = (unsigned long int)ts.tv_sec * 1000LL + (unsigned long int)ts.tv_nsec / 1000000LL;

	cout<<end_ - start_;

	double time = ((double)my_timer_global) / CLOCKS_PER_SEC;
	return time > 1.7 && time < 2.3;
}

bool TestRTTBase::test_timer_recursive(){

	TIMER_CREATE(my_timer_out);
	TIMER_CREATE(my_timer_in);

	TIMER_MEASURE(my_timer_out,
			TIMER_MEASURE(my_timer_in,
					for(int i = 0; i < 1000; i++){
						mysleep(1);
					}
			);
	);

	TIMER_REPORT(my_timer_out);
	TIMER_REPORT(my_timer_in);


	double time = ((double)my_timer_out_global) / CLOCKS_PER_SEC;
	return time > 9 && time < 11;
}



/* -----------------------------------------------------------
Function: void TestRTTBase::run()

Description:
Runs all the basic tests for a this test suite.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestRTTBase::run(){
	Test::run();
	//----------------------------------------------------

	TEST_FUNCTION(test_timer)

	TEST_FUNCTION(test_timer_recursive)

	//-----------------------------------------------------
	finish();
}

/* -----------------------------------------------------------
Function: void TestRTTBase::finish()

Description:
Memory deallocation.

In:
void

Out:
void
-----------------------------------------------------------------*/
void TestRTTBase::finish(){

	//-----------------------------------------------------

	//-----------------------------------------------------
	Test::finish();
}


