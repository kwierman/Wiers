#ifndef WRail_h_
#define WRail_h_

#include "WConnection.h"

namespace Wiers{

	class WRail : public WConnection{

	public:
		WRail(double voltage) : WConnection() {SetVoltage(voltage);}
		bool IsValid(){return true;}
		void DCUpdate(){}
		void NotifyOnInput(){}
		void NotifyOnOutput(){}
		void AcceptVisitorUpstream(WElementVisitor*){}
		void AcceptVisitorDownStream(WElementVisitor*){}
	};

}


#endif //WRail_h_