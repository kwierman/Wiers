#ifndef Rail_h_
#define Rail_h_

#include "Connection.h"

#include <iostream>

namespace Wiers{

	class Rail : public Connection{

	public:
		Rail(double x) : Connection() {voltage = x;}

		void Update(){}

		virtual bool SetVoltage(double){
			std::cout<<"Attempting to Change Rail Voltage"<<std::endl;
			return false;
		}//voltages are not set by other 

	};
}

#endif //Rail_h_