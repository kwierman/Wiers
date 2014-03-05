#include "WComponentDCVisitor.h"
namespace Wiers{

	void WComponentDCVisitor::UpdateForward(){
		if(!input || !output){
			std::cout<<"Incomplete type. Exiting..."<<std::endl;
		}
		if(GetDeltaV()==0 && this->current==0){
			std::cout<<"Component: "<<GetID()<<" Has no voltage and no current."<<std::endl;
		}
		if( GetDeltaV() != resistance*current ){		
			std::cout<<"Component: "<<GetID()<<" Updating..."<<std::endl;
			std::cout<<"  Old Voltage: "<<resistance*current<<"  New Voltage: "<<GetDeltaV()<<std::endl;
			this->current = GetDeltaV()/(this->resistance);
			input->UpdateInput();
			output->UpdateOutput();
		}
	}
	void WComponentDCVisitor::UpdateBackward(){
		if(!input || !output){
			std::cout<<"Incomplete type. Exiting..."<<std::endl;
		}
		if(GetDeltaV()==0 && this->current==0){
			std::cout<<"Component: "<<GetID()<<" Has no voltage and no current."<<std::endl;
		}
		if( GetDeltaV() != resistance*current ){		
			std::cout<<"Component: "<<GetID()<<" Updating..."<<std::endl;
			std::cout<<"  Old Voltage: "<<resistance*current<<"  New Voltage: "<<GetDeltaV()<<std::endl;
			this->current = GetDeltaV()/(this->resistance);
			output->UpdateOutput();
			input->UpdateInput();
		}
	}
}

	