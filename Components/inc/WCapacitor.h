#ifndef WCapacitor_h_
#define WCapacitor_h_

#include "WComponent.h"

namespace Wiers{
	class WCapacitor : public WComponent{

	public:
		WCapacitor(double cap) : WComponent(0.0, cap){}
	};

}


#endif //WCapacitor_h_