#include "Resistor.h"
#include "Rail.h"
#include "Utilities.h"
#include <iostream>

using namespace Wiers;
int main(){

	signal(SIGINT, signal_callback_handler);
	signal(SIGABRT, signal_callback_handler);
	signal(SIGBUS ,signal_callback_handler);
	signal(SIGSEGV ,signal_callback_handler);

	Resistor* a = new Resistor(1);
	Resistor* b = new Resistor(5);
	Resistor* c = new Resistor(10);

	Rail* d = new Rail(10);
	Rail* e = new Rail(0);

	a->SetInput(	d->GetOutput() );
	b->SetInput(	a->GetOutput() );
	c->SetInput(	b->GetOutput() );
	c->SetOutput(	e->GetInput()  );

	//f->SetInput(b);
	//f->SetOutput(e);

	a->Update();

	std::cout<<a->GetVoltage()<<std::endl;;
	std::cout<<b->GetVoltage()<<std::endl;
	std::cout<<c->GetVoltage()<<std::endl;
	std::cout<<f->GetVoltage()<<std::endl;

	return 0;
}

//Logical Steps here
//start connecting components
//call update on one component
//it tries to reconcile the voltage drop with the current across it

//if voltage != current, the it tells it's connection that it needs a voltage update and current update
	//this part needs to be egalitarian