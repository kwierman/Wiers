#ifndef Connection_h_
#define Connection_h_

#include <vector>

namespace Wiers{
	class Component;

	class Connection{
		double voltage;
		std::vector<Component*> inputs;
		std::vector<Component*> outputs;
		typedef std::vector<Component*>::iterator cIt;
	public:
		double GetVoltage(){return voltage;}

		void NotifyNewCurrentOnInput(double);
		void NotifyNewCurrentOnOutput(double);
	};

}

#endif //Connection_h_