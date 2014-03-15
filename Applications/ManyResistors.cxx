#include "WComponent.h"
#include "WRail.h"
#include "WUtilities.h"
#include <iostream>
#include <iomanip>

using namespace Wiers;
int main(){

	signal(SIGINT, signal_callback_handler);
	signal(SIGABRT, signal_callback_handler);
	signal(SIGBUS ,signal_callback_handler);
	signal(SIGSEGV ,signal_callback_handler);

	WRail a(10.0);
	WRail b(0.0);

	const int n_resistors = 100;

	WComponent c[n_resistors];
	c[0] = WComponent(10);
	c[0].SetInput(&a);
	for(int i =1;i<(n_resistors-1);i++){
		c[i] = WComponent(10.0*(i+1));
		c[i].SetInput(c[i-1].GetOutput() );
	}
	c[n_resistors-1] = WComponent(10.0*n_resistors);
	(c[n_resistors-1]).SetInput( c[n_resistors-2].GetOutput() );

	c[n_resistors-1].SetOutput(&b);

	c[0].UpdateWithVisitor();;

	for(int i=0; i<n_resistors; i++){
		std::cout<<"Component: "<<i<<std::endl;
		std::cout<<"  V:"<<std::setprecision(16)<<"  "<<c[i].GetDeltaV()<<std::endl;
		std::cout<<"  I:"<<std::setprecision(16)<<"  "<<c[i].GetCurrent()<<std::endl;
	}

	return 0;
}
