#ifndef Resistor_h_
#define Resistor_h_

#include "Component.h"

namespace Wiers{

	class Resistor : public Component{
		double voltage;
		double current;
		double resistance;

	public:
		Resistor(double x) : resistance(x), voltage(0.0),current(0.0){}



	};
}


#endif //Resistor_h_