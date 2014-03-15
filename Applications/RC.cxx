#include "WResistor.h"
#include "WCapacitor.h"
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
	WRail b(0.0);

	WResistor r(10);//Make this a 10
	WCapacitor c(0.5);

	r.SetInput(&a);
	c.SetInput(r.GetOutput() );

	c.SetOutput(&b);

	c.ACUpdate(0.1, 10.0);
	return 0;
}
