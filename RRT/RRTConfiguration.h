/*
 * RRTConfiguration.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef RRTCONFIGURATION_H_
#define RRTCONFIGURATION_H_

#include <iostream>
using namespace std;

class RRTConfiguration {
	public:
		RRTConfiguration(){}
		virtual ~RRTConfiguration(){}

		virtual string toString() const {
			return string("[Empty configuration]");
		}

		friend ostream&	operator<<(ostream& os, const RRTConfiguration& conf){
			os<< conf.toString();
			return os;
		}
};

#endif /* RRTCONFIGURATION_H_ */
