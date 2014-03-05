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
	WRail c(0.0);

	b.SetInput(&a);
	b.SetOutput(&c);

	b.DCUpdate();

	std::cout<<b.GetDeltaV()<<std::endl;
	std::cout<<b.GetCurrent()<<std::endl;

	return 0;
}