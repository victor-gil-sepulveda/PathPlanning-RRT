/////////////////////////////////////////////////////////////////////////////
/// \file ProteinRMSDMetric.h
/// \brief bla, bla
///
/// \author vgil
/// \date 20/07/2011
/////////////////////////////////////////////////////////////////////////////

#ifndef PROTEINRMSDMETRIC_H_
#define PROTEINRMSDMETRIC_H_

#include "../../../../BaseAlgorithms/RRTMetric.h"


//-----------------------------
// Package
//-----------------------------
namespace PathPlanning{
	namespace Metrics{
//------------------------------
class ProteinRMSDMetric: public RRTMetric {
	public:
					ProteinRMSDMetric	();
		virtual 	~ProteinRMSDMetric	();

	private:
		double		calc_distance	 	(RRTNode* first, RRTNode* second);
};
//------------------------------
	};
};

#endif /* PROTEINRMSDMETRIC_H_ */
