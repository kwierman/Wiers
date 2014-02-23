#ifndef Rail_h_
#define Rail_h_

#include "Component.h"

namespace Wiers{

	class Rail : public Component{
		double voltage;

	public:
		Rail(double x) : voltage(x) {}

		double GetInputImpedance(){return 0;};
		double GetOutputImpedance(){return 0;}

		double GetInputVoltage() {return voltage;}
		double GetOutputVoltage(){return voltage;}
	};
}

#endif //Rail_h_