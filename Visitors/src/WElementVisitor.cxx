#include "WElementVisitor.h"
#include "WComponent.h"

#include <iostream>

namespace Wiers{

	void WElementVisitor::Go(){
		while(! primary->IsValid() ) {
			primary->AcceptVisitorUpstream(this);
			while(!fQueue.empty()){
				WElement* el = fQueue.front();
				if(! (el->IsValid() ) ){
					el->AcceptVisitorUpstream(this);
				}
				fQueue.pop();
			}
			primary->AcceptVisitorDownStream(this);
			while(!fQueue.empty()){
				WElement* el = fQueue.front();
				if(! (el->IsValid() ) ){
					el->AcceptVisitorDownStream(this);
				}
				fQueue.pop();
			}
		}
	}
}