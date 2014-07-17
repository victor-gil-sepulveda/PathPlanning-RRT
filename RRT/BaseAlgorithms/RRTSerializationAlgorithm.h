/*
 * RRTSerializationAlgorithm.h
 *
 *  Created on: May 25, 2011
 *      Author: vgil
 */

#ifndef RRTSERIALIZATIONALGORITHM_H_
#define RRTSERIALIZATIONALGORITHM_H_


#include <vector>
#include <sstream>
using namespace std;

#include "RRTBaseAlgorithm.h"
#include "../RRTNode.h"

class RRTSerializationAlgorithm: public RRTBaseAlgorithm {

		public:
								RRTSerializationAlgorithm	();
			virtual 			~RRTSerializationAlgorithm	();

			virtual bool		saveState						(vector<RRTNode*>& nodes);
			virtual	bool		saveAllStates					();

			string 				getBasePath					() const;
			unsigned int 		getCurrentFile				() const;
			string 				getBaseFile					() const;
			unsigned int 		getMaxFiles					() const;
			string				getFileType					() const;
			bool				getClean					() const;
			string				getLastFilePath				();
			bool 				getSaveAllStates			() const;
			bool 				getSaveState				() const;

			void 				setBasePath					(string basePath);
			void 				setCurrentFile				(unsigned int currentFile);
			void 				setBaseFile					(string baseFile);
			void 				setMaxFiles					(unsigned int maxFiles);
			void 				setFileType					(string fileType);
			void				setClean					(bool clean);
			void 				setSaveAllStates			(bool save_all_states);
			void 				setSaveState				(bool save_state);


		protected:



			virtual bool 		do_save						(vector<RRTNode*>& nodes, string path) = 0;
			virtual bool		do_save_all					()=0;
			virtual void		do_clean					()=0;
			int 				get_max_numb				();

			string 				base_path;
			string				base_file;
			string				file_type;
			unsigned int		current_file;
			unsigned int 		max_files;
			unsigned int 		max_ciphers;
			bool 				clean_the_room;
			string 				path;
			bool 				save_state;
			bool 				save_all_states;

};

#endif /* RRTSERIALIZATIONALGORITHM_H_ */
