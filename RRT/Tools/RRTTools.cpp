/*
 * RRTTools.cpp
 *
 *  Created on: May 30, 2011
 *      Author: vgil
 */

#include "RRTTools.h"

void RRTTools::File::convertBMPtoRRTField(string the_bmp, string the_output_field){
	// Invoke python script to convert a file
	std:: stringstream command;

	command<<"python src/PathPlanning/RRT/Tools/ConversorImagenes.py "
			<<the_bmp<<" "
			<<the_output_field;

	system(command.str().c_str());
}
