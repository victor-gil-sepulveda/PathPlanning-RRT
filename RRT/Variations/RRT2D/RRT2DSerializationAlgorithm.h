/*
 * RRT2DSerializationAlgorithm.h
 *
 *  Created on: 29/05/2011
 *      Author: vgil
 */

#ifndef RRT2DSERIALIZATIONALGORITHM_H_
#define RRT2DSERIALIZATIONALGORITHM_H_

#include <fstream>

#include "../../BaseAlgorithms/RRTSerializationAlgorithm.h"
#include "RRT2DConfiguration.h"


class RRT2DSerializationAlgorithm: public RRTSerializationAlgorithm {
	public:
							RRT2DSerializationAlgorithm	();
		virtual 			~RRT2DSerializationAlgorithm();

		RRTNode*			getGoalNode					() const;
		string				getBackgroundImage			() const;
		unsigned int		getHeight					() const;
		unsigned int 		getWidth					() const;
		string&		 		getLastImage				();

		void 				setGoalNode					(RRTNode *goalNode);
		void				setBackgroundImage			(string path);
		void 				setWidth					(unsigned int w);
		void				setHeight					(unsigned int h);
		void				setLastImage				(string s);

	private:
		virtual bool 		do_save						(vector<RRTNode*>& nodes, string path);
		virtual bool 		do_save_all					();
		virtual void		do_clean					();

		RRTNode* 			goal_node;
		string 				background_image;
		unsigned int 		width;
		unsigned int 		height;
		string 				last_image;
};

#endif /* RRT2DSERIALIZATIONALGORITHM_H_ */
