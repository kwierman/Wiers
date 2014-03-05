#ifndef WComponentDCVisitor_h_
#define WComponentDCVisitor_h_

#include "WElementVisitor.h"

namespace Wiers{

	class WComponent;
	class WComponentDCVisitor : public WElementVisitor {
		WComponent* current;
		WConnection* next;
	public:
		void UpdateForward();
		void UpdateBackward();
	};
}


#endif //WComponentDCVisitor_h_