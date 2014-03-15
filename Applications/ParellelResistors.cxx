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

	WComponent a(5.0);

	WComponent b(10);

	WComponent c(15);

	WRail d(10.0);

	WRail e(0.0);

	a.SetInput( &d);

	b.SetInput( a.GetOutput() );

	c.SetInput( a.GetOutput() );

	b.SetOutput( &e );

	c.SetOutput( &e );

	a.UpdateWithVisitor();

	std::cout<<std::endl;
	std::cout<<"A Voltage: "<<a.GetDeltaV()<<std::endl;
	std::cout<<"A Current: "<<a.GetCurrent()<<std::endl;
	std::cout<<"B Voltage: "<<b.GetDeltaV()<<std::endl;
	std::cout<<"B Current: "<<b.GetCurrent()<<std::endl;
	std::cout<<"C Voltage: "<<c.GetDeltaV()<<std::endl;
	std::cout<<"C Current: "<<c.GetCurrent()<<std::endl;
	std::cout<<"  Sum Currents: "<<b.GetCurrent()+c.GetCurrent()<<std::endl;

	return 0;
}
