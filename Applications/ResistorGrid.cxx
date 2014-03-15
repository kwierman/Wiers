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
	WRail b(0.0);

	WComponent parellel[100];//thiss goes for the rows of resistors
	WComponent perpendicular[99];//this goes for the columns of resistors
/*
	for (int i=0; i<10;i++){
		for(int j=0; j<10;j++){
			c[j*(i+1)] = WComponent(10000.0);
			if(i>0) c[j*(i+1)].SetInput(c[j*i].GetOutput() );
			if(j>0 ) c[j*(i+1)].SetInput(c[j*(i+1)-1].GetOutput() );

		}
	}
*/
/*
	c[0] = WComponent(10);
	c[0].SetInput(&a);
	for(int i =1;i<99;i++){
		c[i] = WComponent(10.0*i);
		c[i].SetInput(c[i-1].GetOutput() );
	}
	c[99] = WComponent(990.0);
	(c[99]).SetInput( c[98].GetOutput() );

	c[99].SetOutput(&b);

	c[0].DCUpdate();

	for(int i=0; i<100; i++){
		std::cout<<"Component: "<<i<<std::endl;
		std::cout<<"  "<<c[i].GetDeltaV()<<std::endl;
		std::cout<<"  "<<c[i].GetCurrent()<<std::endl;
	}
	*/
	return 0;
}
