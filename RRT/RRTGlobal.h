/*
 * RRTGlobal.h
 *
 *  Created on: Jun 1, 2011
 *      Author: vgil
 */

#ifndef RRTGLOBAL_H_
#define RRTGLOBAL_H_


#include <ctime>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

#define _RRT_NO_DEBUG_ 		0
#define _RRT_DEBUG_LOW_ 	1
#define _RRT_DEBUG_MEDIUM_ 	2
#define _RRT_DEBUG_HIGH_ 	3

#define _RRT_DEBUG_LEVEL_ 	_RRT_DEBUG_LOW_

#define _RRT_DEBUG_(L,C) if(_RRT_DEBUG_LEVEL_ >= L ){ C }

#define TIMER_CREATE(N) timespec N##_time;\
						unsigned long int N##_time_start, N##_time_end;\
						unsigned long int N##_global;\
						unsigned int N##_times;\
						N##_global=0;\
						N##_times = 0;

#define TIMER_MEASURE(N, C) clock_gettime(CLOCK_REALTIME, &N##_time); \
							N##_time_start = (unsigned long int)N##_time.tv_sec * 1000LL + (unsigned long int)N##_time.tv_nsec / 1000000LL;\
							C \
							clock_gettime(CLOCK_REALTIME, &N##_time); \
							N##_time_end = (unsigned long int)N##_time.tv_sec * 1000LL + (unsigned long int)N##_time.tv_nsec / 1000000LL; \
							N##_global += (N##_time_end - N##_time_start); \
							N##_times++;

#define TIMER_REPORT(N) cout<<#N << " took " << ((double)N##_global ) / 1000 <<" seconds ("<<(((double)N##_global)/N##_times) /1000<<"s mean exec. time)"<< endl;




// needs -lrt (real-time lib)


#endif /* RRTGLOBAL_H_ */
