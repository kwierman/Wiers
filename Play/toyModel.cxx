#include <iostream>

double accuracy = 1.e-6;//this is the voltage step size.

struct Connection;
struct Component{
	double impedance;
	double current;
	Connection* input;
	Connection* output;
	Component(double x) : impedance(x), current(0.0){}

};
struct Connection{
	double voltage;
	Component* input;
	Component* output;
	Connection(double x) : voltage(x){}
};

double ExternalCompCurrent(Component& comp){
	return (comp.input->voltage-comp.output->voltage)/(comp.impedance);
}

bool IsCurrentCorrect(Component& comp  ){
	return comp.current == ExternalCompCurrent(comp);
}

void NotifyNewVoltage(Connection& conn, double voltage){
	conn.voltage = voltage;
	conn.output->current = 
}

int main(){
	Connection ground(0.0);
	Connection vCC(10.0);
	Connection in1(0.0);
	Connection in2(0.0);

	Component res1(1.0);
	Component res2(5.0);
	Component res3(10.0);

	//now connect them up:
	res1.input = &vCC;
	res1.output = &in1;

	res2.input = &in1;
	res2.output = &in2;

	res3.input = &in2;
	res3.output = &ground;


	//for each of the resistors	

	while( !IsCurrentCorrect(res1) ){
		std::cout<<"resistor 1 current is output of balance: "<<res1.current<<std::endl;
		std::cout<<"\tShould be: "<< ExternalCompCurrent(res1) <<std::endl;
		res1.current+=accuracy;
		NotifyNewVoltage(in1, vCC - res1.current*res1.impedance);	
	}
}


//Ohm's law: V=IR