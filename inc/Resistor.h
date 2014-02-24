#ifndef Resistor_h_
#define Resistor_h_

#include "Component.h"

#include <iostream>

namespace Wiers{

	class Resistor : public Component{
		double resistance;//<! the fairly static impedance of the device
		double current;//<! the dynamic current across this device.

	public:
		//Resistor(double x) : resistance(x), current(0.0) {}

		void Update();

	};
}


#endif //Resistor_h_