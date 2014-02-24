#include "Component.h"
#include "Connection.h"

#include <iostream>

namespace Wiers{
	unsigned int Component::count=0;

	void Component::SetInput(Connection* other){
		this->input = other;
	}
	void Component::SetOutput(Connection* other){
		this->output = other;
	}

	Connection* Component::GetInput(){
		if(!input) input = new Connection();
		return input;
	}
	Connection* Component::GetOutput(){
		if(!output) output = new Connection();
		return output;
	}
	double Component::GetDeltaV(){
		std::cout<<"Component: "<<GetID()<<" Voltage: "<<this->output->GetVoltage() - this->input->GetVoltage()<<std::endl;
		return this->output->GetVoltage() - this->input->GetVoltage();
	}

	void Component::Update(){
		//the necessary update occurs when the 
		if(GetDeltaV()==0 && this->current==0)
			return;//we're good

		if( GetDeltaV() != resistance*current ){
			std::cout<<"Resistor: "<<GetID()<<"Updating..."<<std::endl;


			std::cout<<"  Old Voltage: "<<resistance*current<<"  New Voltage: "<<GetDeltaV()<<std::endl;
			bool success=true;
			if(!(input->ChangeVoltage( GetDeltaV() ) ) )
				success = output->ChangeVoltage( -GetDeltaV( ) );
			if(!success )
				std::cout<<"Voltage Change not successful"<<std::endl;

		}

	}
}
