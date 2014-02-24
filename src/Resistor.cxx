#include "Resistor.h"
#include "Connection.h"

namespace Wiers{


	void Resistor::Update(){
		//the necessary update occurs when the 
		if(GetDeltaV()==0 && this->current==0)
			return;

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