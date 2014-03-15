#ifndef WResistor_h_
#define WResistor_h_

#include "WComponent.h"

namespace Wiers{
	class WResistor : public WComponent{

	public:
		WResistor(double res) : WComponent(res, 0.0){}
	};

}


#endif //WResistor_h_