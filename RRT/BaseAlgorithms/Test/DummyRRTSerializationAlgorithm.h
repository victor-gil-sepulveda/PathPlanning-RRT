/*
 * DummyRRTSerializationAlgorithm.h
 *
 *  Created on: 28/05/2011
 *      Author: vgil
 */

#ifndef DUMMYRRTSERIALIZATIONALGORITHM_H_
#define DUMMYRRTSERIALIZATIONALGORITHM_H_

#include "../RRTSerializationAlgorithm.h"

class DummyRRTSerializationAlgorithm: public RRTSerializationAlgorithm {
	public:
		DummyRRTSerializationAlgorithm(){}
		virtual ~DummyRRTSerializationAlgorithm(){}

		string getSavedFile(){
			return saved_file;
		}

		virtual bool do_save(vector<RRTNode*>& nodes, string path){
			saved_file = path;
			return true;
		}

		virtual bool do_save_all(){
				return true;
		}

		virtual void do_clean(){

		}

		string saved_file;
};

#endif /* DUMMYRRTSERIALIZATIONALGORITHM_H_ */
