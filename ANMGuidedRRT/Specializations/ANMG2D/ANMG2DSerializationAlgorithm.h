/*
 * ANMG2DSerializationAlgorithm.h
 *
 *  Created on: Jun 9, 2011
 *      Author: vgil
 */

#ifndef ANMG2DSERIALIZATIONALGORITHM_H_
#define ANMG2DSERIALIZATIONALGORITHM_H_

#include <fstream>

#include "../../../RRT/BaseAlgorithms/RRTSerializationAlgorithm.h"
#include "../../../RRT/Variations/RRT2D/RRT2DSerializationAlgorithm.h"

class ANMG2DSerializationAlgorithm: public RRTSerializationAlgorithm {
		public:
											ANMG2DSerializationAlgorithm	();
			virtual							~ANMG2DSerializationAlgorithm	();

			RRTSerializationAlgorithm*		getTreeSerializer				() const;
			void 							setTreeSerializer				(RRTSerializationAlgorithm *tree_serializer);

		protected:

			RRTSerializationAlgorithm*				tree_serializer;

			virtual bool 		do_save				(vector<RRTNode*>& nodes, string path);
			virtual bool		do_save_all			();
			virtual void		do_clean			();
};


#endif /* ANMG2DSERIALIZATIONALGORITHM_H_ */
