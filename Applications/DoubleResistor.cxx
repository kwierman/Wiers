#include "WComponent.h"
#include "WRail.h"
#include "WUtilities.h"
#include <iostream>

using namespace Wiers;
int main(){

	signal(SIGINT, signal_callback_handler);
	signal(SIGABRT, signal_callback_handler);
	signal(SIGBUS ,signal_callback_handler);
	signal(SIGSEGV ,signal_callback_handler);

	WRail a(10.0);
	WComponent b(5.0);
	
	b.SetInput(&a);
	
	WComponent c(10.0);
	
	c.SetInput(b.GetOutput() );
	
	WRail d(0.0);
	
	c.SetOutput(&d);
	
	//b.DCUpdate();
	b.UpdateWithVisitor();
	
	std::cout<<c.GetDeltaV()<<std::endl;
	std::cout<<c.GetCurrent()<<std::endl;

	return 0;
}
