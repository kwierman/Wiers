#ifndef WInductor_h_
#define WInductor_h_

#include "WConnection.h"

namespace Wiers{
	class WInductor : public WConnection{

	public:
		WInductor(double ind) : WConnection(0.0, ind){}
	};

}


#endif WInductor_h_