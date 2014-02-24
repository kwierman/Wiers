#ifndef Rail_h_
#define Rail_h_

#include "Component.h"

namespace Wiers{

	class Rail : public Component{
		double voltage;

	public:
		Rail(double x) : voltage(x) {}

		void Update(){}

	};
}

#endif //Rail_h_