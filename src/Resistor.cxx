#include "Resistor.h"
#include "Connection.h"

namespace Wiers{


	void Resistor::Update(){
		double voltage_drop = input->GetVoltage()-output->GetVoltage();
		if(voltage_drop != resistance*current ){
			voltage_drop = input->GetVoltage()-output->GetVoltage();
			std::cout<<"Resistor: "<<GetID()<<"Updating..."<<std::endl;
			std::cout<<"  Old Voltage: "<<resistance*current<<"  New Voltage: "<<voltage_drop<<std::endl;
			//you have to play with input and output here to get the voltage back.
			input->NotifyNewCurrentOnOutput(voltage_drop/resistance );
			output->NotifyNewCurrentOnInput(voltage_drop/resistance);

		}

	}
}