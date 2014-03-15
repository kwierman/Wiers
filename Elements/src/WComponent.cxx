#include "WComponent.h"
#include "WConnection.h"
#include "WElementVisitor.h"
#include "WMath.h"

#include <iostream>

namespace Wiers{

	long double WComponent::fACCurrentMax=1.e6;

	bool WComponent::IsValid(){
		if(n_iterations>max_iterations) return true;
		return ( GetDeltaV() == this->fCurrent * this->fResistivity );
	}

	void WComponent::SetInput(WConnection* other){
		this->input = other;
		this->input->SetOutput(this);
	}
	void WComponent::SetOutput(WConnection* other){
		this->output = other;
		this->output->SetInput(this);
	}
	WConnection* WComponent::GetInput(){
		if(!input){
			input = new WConnection();
			input->SetOutput(this);
		}
		return input;
	}
	WConnection* WComponent::GetOutput(){
		if(!output) {
			output = new WConnection();
			output->SetInput(this);
		}
		return output;
	}
	long double WComponent::GetDeltaV(){
		return this->output->GetVoltage() - this->input->GetVoltage();
	}
	long double WComponent::GetDeltaACV(){
		return output->GetACVoltage() - input->GetACVoltage();
	}

	void WComponent::ACUpdate(long double timeStep, long double timeToGo){
		fGlobalTime=0.0;
		n_iterations=0;
		while (fGlobalTime<= timeToGo){
			fCurrentTimeStep = timeStep;
			//for the current time step
			SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
			while(!IsValid() ){
				fACCurrent += GetDeltaACV()*fReactance/fCurrentTimeStep;
				if(fACCurrent>fACCurrentMax) fCurrentTimeStep /=(fACCurrent/fACCurrentMax);
				input->CheckACInput();
				output->CheckACOutput();
				SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
			}
			//at this point, they've found a  steady state solution
			fCurrent+=fACCurrent;
			input->UpdateACInput();
			output->UpdateACOutput();
			fGlobalTime+=fCurrentTimeStep;
			UpdateWithVisitor();
			std::cout<<fCurrent<<std::endl;
		}
	}

	void WComponent::CheckACInput(){
		SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
		while(!IsValid() ){
			fACCurrent += GetDeltaACV()*fReactance/fCurrentTimeStep;
			if(fACCurrent>fACCurrentMax) fCurrentTimeStep /=(fACCurrent/fACCurrentMax);
			input->CheckACInput();
			SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
		}
	}
	void WComponent::CheckACOutput(){
		SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
		while(!IsValid() ){
			fACCurrent += GetDeltaACV()*fReactance/fCurrentTimeStep;
			if(fACCurrent>fACCurrentMax) fCurrentTimeStep /=(fACCurrent/fACCurrentMax);
			output->CheckACOutput();
			SetValid(GetDeltaACV() == fCurrentTimeStep*fACCurrent/fReactance );
		}
	}

	void WComponent::UpdateACInput(){
		fCurrent+=fACCurrent;
		input->UpdateACInput();
	}
	void WComponent::UpdateACOutput(){
		fCurrent+=fACCurrent;
		output->UpdateACOutput();
	}

	void WComponent::UpdateWithVisitor(){
		WElementVisitor visitor;
		visitor.set_primary(this);
		visitor.Go();
	}
	void WComponent::AcceptVisitorUpstream(WElementVisitor* visitor ){
		++n_iterations;
		this->fCurrent = GetDeltaV()/(this->fResistivity);
		visitor->put_on_stack(input);
	}
	void WComponent::AcceptVisitorDownStream(WElementVisitor* visitor){
		++n_iterations;
		this->fCurrent = GetDeltaV()/(this->fResistivity);
		visitor->put_on_stack(output);
	}
}