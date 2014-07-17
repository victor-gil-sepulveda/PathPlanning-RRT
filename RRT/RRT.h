/*
 * RRT.h
 *
 *  Created on: 11/01/2011
 *      Author: victor
 */

#ifndef RRT_H_
#define RRT_H_




#include <vector>
#include <iostream>
using namespace std;

#include "RRTGlobal.h"
#include "RRTNode.h"
#include "BaseAlgorithms/RRTMetric.h"
#include "BaseAlgorithms/SamplingAlgorithm.h"
#include "BaseAlgorithms/ExpansionAlgorithm.h"
#include "BaseAlgorithms/NearestNeighbourAlgorithm.h"
#include "BaseAlgorithms/ColisionTest.h"
#include "BaseAlgorithms/RRTSerializationAlgorithm.h"
#include "BaseAlgorithms/CompletionCheck.h"


class RRT{

	public:
							RRT						(
														RRTMetric* metric,
														SamplingAlgorithm* sampAlg,
														ExpansionAlgorithm* expAlg,
														NearestNeighbourAlgorithm* nnAlg,
														ColisionTest* colTest,
														CompletionCheck* compCheck,
														RRTSerializationAlgorithm* rwAlgorithm
													);
		virtual 			~RRT					();
		void 				run						(RRTNode* s = NULL);

		bool				serialize				(char* path);
		bool				deserialize				(char* path);

		void	setStartNode						(RRTNode* start);
		void 	setColisionTestAlgorithm			(ColisionTest *colTest);
		void 	setExpansionAlgorithm				(ExpansionAlgorithm *expAlg);
		void 	setMetric							(RRTMetric *metric);
		void 	setNearestNeighbourAlgorithm		(NearestNeighbourAlgorithm *nnAlg);
		void 	setRwAlgorithm						(RRTSerializationAlgorithm *rwAlgorithm);
		void 	setSamplingAlgorithm				(SamplingAlgorithm *sampAlg);
		void 	setCompletionCheck					(CompletionCheck* compCheck);

		RRTNode*					getStartNode						();
		vector<RRTNode*>& 			getNodes							();
		ColisionTest*				getColisionTestAlgorithm			() const;
		ExpansionAlgorithm*			getExpansionAlgorithm				() const;
		RRTMetric*					getMetric							() const;
		NearestNeighbourAlgorithm*	getNearestNeighbourAlgorithm		() const;
		RRTSerializationAlgorithm*	getRwAlgorithm						() const;
		SamplingAlgorithm *			getSamplingAlgorithm				() const;
		CompletionCheck*			getCompletionCheck					() const;

		RRT& 						operator= 							(const RRT& rrt);
		bool 						operator== 							(const RRT& rrt) const;
		bool 						operator!= 							(const RRT& rrt) const;
		friend ostream& 			operator<< 							(ostream& os, const RRT& rrt);

	private:


		// Starting and ending nodes
		RRTNode*					start;
		// Book-keeping
		vector<RRTNode*> 			nodes;


		// Algorithms (RRT is a composition of other small algorithms)
		RRTMetric* 					metric;
		SamplingAlgorithm* 			sampAlg;
		ExpansionAlgorithm* 		expAlg;
		NearestNeighbourAlgorithm* 	nnAlg;
		ColisionTest* 				colTest;
		CompletionCheck*			compCheck;
		RRTSerializationAlgorithm* 	rwAlgorithm;


		// Functions
		void				destroy						();
		void 				add_node					(RRTNode* father,RRTNode* son); // addVertex + addEdge

};

#endif /* RRT_H_ */
