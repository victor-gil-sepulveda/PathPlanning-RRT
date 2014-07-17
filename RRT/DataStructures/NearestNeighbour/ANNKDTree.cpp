/*
 * ANNKDTree.cpp
 *
 *  Created on: 30/05/2011
 *      Author: vgil
 */

#include "ANNKDTree.h"

ANNKDTree::ANNKDTree() {
	ANNpointArray pa;

	tree = new ANNkd_tree(pa,0,0);
}

ANNKDTree::~ANNKDTree() {
	delete tree;
}
