#include "WConnectionVisitor.h"

namespace Wiers{

	void WConnectionVisitor::UpdateUpstream(){
		if( GetTotalCurrent() != 0.0 ){		
			std::cout<<"Connection: "<<" Updating..."<<std::endl;
			this->voltage += GetTotalCurrent()*( GetInputImpedance()- GetOutputImpedance() );
			std::cout<<"  Voltage: "<<this->voltage<<std::endl;
			for(comp_it it = inputs.begin(); it!=inputs.end();++it )(*it)->UpdateInput();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it )(*it)->UpdateOutput();
		}
	}
	void WConnectionVisitor::UpdateDownstream(){
		if( GetTotalCurrent() != 0.0 ){		
			std::cout<<"Connection: "<< GetTotalCurrent() <<" Updating..."<<std::endl;
			this->voltage -= GetTotalCurrent()*( GetInputImpedance()- GetOutputImpedance() ) ;
			std::cout<<"  Voltage: "<<this->voltage<<std::endl;;
			for(comp_it it = outputs.begin(); it!=outputs.end();++it )(*it)->UpdateOutput();
			for(comp_it it = inputs.begin(); it!=inputs.end();++it )(*it)->UpdateInput();
		}
	}

}
