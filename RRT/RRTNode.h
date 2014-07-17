/*
 * RRTNod.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef RRTNOD_H_
#define RRTNOD_H_
#include <iostream>
using namespace std;

#include "../../Molecules/AtomSet/NodeContainer.h"
#include "RRTConfiguration.h"

// Definition of a node
class RRTNode: public NodeContainer<RRTConfiguration* > {
	public:
		RRTNode(){setDataP(NULL);}
		virtual ~RRTNode(){ if(getData()!=NULL) delete getData();}

		friend ostream&	operator<<(ostream& os, const RRTNode& node){
			os<<"[Node "<<*(const_cast<RRTNode*>(&node)->getData())<<" ]";
			return os;
		}
};

#endif /* RRTNOD_H_ */
