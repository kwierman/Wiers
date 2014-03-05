#ifndef WRail_h_
#define WRail_h_

#include "WConnection.h"

namespace Wiers{

	class WRail : public WConnection{

	public:
		WRail(double voltage) : WConnection() {SetVoltage(voltage);}
		void DCUpdate(){}
		void NotifyOnInput(){}
		void NotifyOnOutput(){}
	};

}


#endif //WRail_h_