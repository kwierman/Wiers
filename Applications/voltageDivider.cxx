#include "Component.h"
#include "Rail.h"
#include "Utilities.h"
#include <iostream>

using namespace Wiers;
int main(){

	signal(SIGINT, signal_callback_handler);
	signal(SIGABRT, signal_callback_handler);
	signal(SIGBUS ,signal_callback_handler);
	signal(SIGSEGV ,signal_callback_handler);

	Component* a = new Component(1);
	Component* b = new Component(5);
	Component* c = new Component(10);

	Rail* d = new Rail(10);
	Rail* e = new Rail(0);

	a->SetInput(	d );
	b->SetInput(	a->GetOutput() );
	c->SetInput(	b->GetOutput() );
	c->SetOutput(	e );

	//f->SetInput(b);
	//f->SetOutput(e);

	a->Update();
	b->Update();
	c->Update();

	std::cout<<a->GetDeltaV()<<std::endl;;
	std::cout<<b->GetDeltaV()<<std::endl;
	std::cout<<c->GetDeltaV()<<std::endl;
	//std::cout<<f->GetDeltaV()<<std::endl;

	return 0;
}

//Logical Steps here
//start connecting components
//call update on one component
//it tries to reconcile the voltage drop with the current across it

//if voltage != current, the it tells it's connection that it needs a voltage update and current update
	//this part needs to be egalitarian