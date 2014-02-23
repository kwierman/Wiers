#include "Resistor.h"
#include "Rail.h"

#include <iostream>

using namespace Wiers;
int main(){

	Resistor* a = new Resistor(5);
	Resistor* b = new Resistor(5);
	Resistor* c = new Resistor(5);

	Rail* d = new Rail(10);
	Rail* e = new Rail(0);

	a->SetInput(d);
	b->SetInput(a);
	c->SetInput(b);
	c->SetOutput(e);

	b->GetVoltage();

	//a->ConnectInput( new Rail(5)  );//connect the input to  a 5V rail
	//b->ConnectInput(a->GetOutput() );
	//c->ConnectInput(a->GetOutput() );
	//b->ConnectOutput(new Rail(0.0) );
	//c->ConnectOutput(new Rail(0.0) );

	//std::cout<<a->GetInput()->GetVoltage()<<std::endl;

	return 0;
}


//if you want to ask the question of what is the voltage at any particular point