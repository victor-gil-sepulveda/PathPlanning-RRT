/*
 * RRT2DConfiguration.h
 *
 *  Created on: May 26, 2011
 *      Author: vgil
 */

#ifndef RRT2DCONFIGURATION_H_
#define RRT2DCONFIGURATION_H_

#include <sstream>
using namespace std;

#include "../../RRTConfiguration.h"
#include "../../../../Tools/stringTools.h"

class RRT2DConfiguration : public RRTConfiguration {
		public:
							RRT2DConfiguration			();
			virtual 		~RRT2DConfiguration			();
			int 			getX						() const;
			int 			getY						() const;
			void 			setX						(int x);
			void 			setY						(int y);

			virtual string 	toString					() const;

		private:
			int x;
			int y;
};

#endif /* RRT2DCONFIGURATION_H_ */
