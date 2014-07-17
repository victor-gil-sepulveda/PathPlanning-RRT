/*
 * ANNKDTree.h
 *
 *  Created on: 30/05/2011
 *      Author: vgil
 */

#ifndef ANNKDTREE_H_
#define ANNKDTREE_H_

#include <ANN/ANN.h>

class ANNKDTree {
	public:
		ANNKDTree();
		virtual ~ANNKDTree();

	ANNkd_tree* tree;
};

#endif /* ANNKDTREE_H_ */
