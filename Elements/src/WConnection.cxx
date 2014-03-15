#include "WConnection.h"
#include "WElementVisitor.h"
#include "WMath.h"

namespace Wiers{
	long double WConnection::fACVoltageMax=1.e6; 

	bool WConnection::IsValid(){
		if(n_iterations>max_iterations) return true;
		return ( GetTotalCurrent() == 0.0 );
	}

	void WConnection::SetInput(WComponent* const other){
		inputs.push_back(other);
	}
	void WConnection::SetOutput(WComponent* const other){
		outputs.push_back(other);
	}
	long double WConnection::GetInputCurrent(){
		long double current = 0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) current+= (*it)->GetCurrent();
		return current;
	}

	long double WConnection::GetOutputCurrent(){
		long double current=0.0;
		for(comp_it it = outputs.begin(); it!=outputs.end();++it ) current+= (*it)->GetCurrent();
		return current;
	}

	long double WConnection::GetTotalCurrent(){
		return GetInputCurrent()-GetOutputCurrent();
	}

	long double WConnection::GetInputImpedance(){
		long double imp =0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) imp+= 1.0/((*it)->GetImpedance() );
		return double(1.0)/imp;
	}

	long double WConnection::GetOutputImpedance(){
		long double imp =0.0;
		for(comp_it it = outputs.begin(); it!=outputs.end();++it ) imp+= 1.0/((*it)->GetImpedance() );
		return 1.0/imp;
	}

	long double WConnection::GetVoltageDifference(){
		return GetTotalCurrent()/(GetInputImpedance()+GetOutputImpedance() );
	}

	void WConnection::ACUpdate(long double timeStep, long double timeToGo){
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
			//DCUpdate();
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

	long double WConnection::GetTotalACCurrent(){
		long double current = 0.0;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) current+= (*it)->GetACCurrent();
			for(comp_it it = outputs.begin(); it!=outputs.end();++it ) current-= (*it)->GetACCurrent();
		return current;		
	}

	void WConnection::UpdateWithVisitor(){
		WElementVisitor visitor;
		visitor.put_on_stack(this);
		visitor.Go();
	}	

	void WConnection::AcceptVisitorUpstream(WElementVisitor* visitor ){
		++n_iterations;
		for(comp_it it = inputs.begin(); it!=inputs.end();++it ) visitor->put_on_stack( (*it) );
		fVoltage += GetVoltageDifference()*GetOutputImpedance();
	}
	void WConnection::AcceptVisitorDownStream(WElementVisitor* visitor ){
		++n_iterations;
		for(comp_it it = outputs.begin(); it != outputs.end();++it ) visitor->put_on_stack( (*it) );
		fVoltage -= GetVoltageDifference()*GetInputImpedance();
	}
}

