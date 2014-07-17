/*
 * RRT2DExpansionAlgorithm.h
 *
 *  Created on: May 27, 2011
 *      Author: vgil
 */

#ifndef RRT2DExpansionAlgorithm_H_
#define RRT2DExpansionAlgorithm_H_

#include "../../BaseAlgorithms/ExpansionAlgorithm.h"
#include "RRT2DConfiguration.h"
#include "RRT2DMetric.h"


class RRT2DExpansionAlgorithm: public ExpansionAlgorithm {
	public:
						RRT2DExpansionAlgorithm		(RRT2DMetric* m);
			virtual 	~RRT2DExpansionAlgorithm	();

		RRTNode*		do_expansion				(RRTNode* from, RRTNode* to);
		unsigned int 	getExpansionDistance		() const;
		void 			setExpansionDistance		(unsigned int expansion_distance);
		unsigned int 	getCollisionMapH			() const;
		unsigned int 	getCollisionMapW			() const;
		void 			setCollisionMapH			(unsigned int collision_map_h);
		void 			setCollisionMapW			(unsigned int collision_map_w);
	private:
		unsigned int 	expansion_distance;
		unsigned int 	collision_map_w;
		unsigned int 	collision_map_h;
};

#endif /* RRT2DExpansionAlgorithm_H_ */
