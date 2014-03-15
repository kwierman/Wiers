#ifndef WElementVisitor_h_
#define WElementVisitor_h_

#include "WElement.h"

#include <queue>

namespace Wiers{

	class WElementVisitor{
		std::queue<WElement*> fQueue;
		bool moving_upstream;
		WElement* primary;

	public:
		WElementVisitor() : moving_upstream(true) {}

		void put_on_stack(WElement* element){ fQueue.push(element); }
		void set_upstream(bool upstream){moving_upstream = upstream;}
		void set_primary(WElement* el){primary=el;}

		void Go();

	};
}

#endif //WElementVisitor_h_