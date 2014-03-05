#include "WConnection.h"
#include "WMath.h"

namespace Wiers{
	double WConnection::fACVoltageMax=1.e6; 

	void WConnection::SetInput(WComponent* const other){
		inputs.push_back(other);
	}
	void WConnection::SetOutput(WComponent* const other){
		outputs.push_back(other);
	}
	double WConnection::GetInputCurrent(){
		double current = 0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) current+= (*it)->GetCurrent();
		return current;
	}

	double WConnection::GetOutputCurrent(){
		double current=0.0;
		for(comp_it it = outputs.begin(); it!=outputs.end();++it ) current+= (*it)->GetCurrent();
		return current;
	}

	double WConnection::GetTotalCurrent(){
		return GetInputCurrent()-GetOutputCurrent();
	}

	double WConnection::GetInputImpedance(){
		double imp =0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) imp+= 1.0/((*it)->GetImpedance() );
		return double(1.0)/imp;
	}

	double WConnection::GetOutputImpedance(){
		double imp =0.0;
		for(comp_it it = outputs.begin(); it!=outputs.end();++it ) imp+= 1.0/((*it)->GetImpedance() );
		return 1.0/imp;
	}

	double WConnection::GetVoltageDifference(){
		return GetTotalCurrent()/(GetInputImpedance()+GetOutputImpedance() );
	}

	void WConnection::DCUpdate(){
		SetValid(GetTotalCurrent() == 0.0 );
		while(!IsValid() ){
			fVoltage += GetVoltageDifference();
			for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->NotifyOnOutput();
			fVoltage -= GetVoltageDifference();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->NotifyOnInput();
			SetValid(GetTotalCurrent() == 0.0  );
		}
	}

	void WConnection::NotifyOnInput(){
		if(n_iterations++ >max_iterations) return;
		SetValid(GetTotalCurrent() == 0.0 );
		if( !IsValid()){		
	  		fVoltage -= GetVoltageDifference()*GetOutputImpedance();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->NotifyOnInput();
		}
	}
	void WConnection::NotifyOnOutput(){
		if(n_iterations++ >max_iterations) return;
		SetValid(GetTotalCurrent() == 0.0 );
		if( !IsValid() ){		
			fVoltage += GetVoltageDifference()*GetInputImpedance();
			for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->NotifyOnOutput();
		}
	}

	void WConnection::ACUpdate(double timeStep, double timeToGo){
		fGlobalTime=0.0;
		n_iterations=0;
		while (fGlobalTime<= timeToGo){
			fCurrentTimeStep = timeStep;
			SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
			while(!IsValid() ){
				fACVoltage += GetTotalACCurrent()*fCurrentTimeStep/fReactance;
				if(fACVoltage>fACVoltageMax) fCurrentTimeStep /=(fACVoltage/fACVoltageMax);
				for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->CheckACInput();
					for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->CheckACOutput();
				SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
			}
			//at this point, they've found a  steady state solution
			fVoltage+=fACVoltage;
			for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->UpdateACInput();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->UpdateACOutput();
			fGlobalTime+=fCurrentTimeStep;
			DCUpdate();
		}
	}
	void WConnection::CheckACInput(){
		SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
		while(!IsValid() ){
			fACVoltage -= GetTotalACCurrent()*fCurrentTimeStep/fReactance;
			if(fACVoltage>fACVoltageMax) fCurrentTimeStep /=(fACVoltage/fACVoltageMax);
			for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->CheckACInput();
			SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
		}
	}
	void WConnection::CheckACOutput(){
		SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
		while(!IsValid() ){
			fACVoltage += GetTotalACCurrent()*fCurrentTimeStep/fReactance;
			if(fACVoltage>fACVoltageMax) fCurrentTimeStep /=(fACVoltage/fACVoltageMax);
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->CheckACOutput();
			SetValid(GetTotalACCurrent() == -fACVoltage*fCurrentTimeStep/fReactance );
		}
	}

	void WConnection::UpdateACInput(){
		fVoltage+=fACVoltage;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) (*it)->UpdateACInput();
	}
	void WConnection::UpdateACOutput(){
		fVoltage+=fACVoltage;
		for(comp_it it = outputs.begin(); it!=outputs.end();++it ) (*it)->UpdateACOutput();
	}

	double WConnection::GetTotalACCurrent(){
		double current = 0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) current+= (*it)->GetACCurrent();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) current-= (*it)->GetACCurrent();
		return current;		

	}
}

