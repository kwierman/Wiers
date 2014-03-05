#include "WComponent.h"
#include "WConnection.h"
#include "WMath.h"

namespace Wiers{

	double WComponent::fACCurrentMax=1.e6;

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
	double WComponent::GetDeltaV(){
		return this->output->GetVoltage() - this->input->GetVoltage();
	}
	double WComponent::GetDeltaACV(){
		return output->GetACVoltage() - input->GetACVoltage();
	}
	void WComponent::DCUpdate(){
		n_iterations=0;
		SetValid(GetDeltaV() == this->fCurrent * this->fResistivity );
		while(!IsValid() ){
			if(n_iterations++ >max_iterations) return;
			this->fCurrent = GetDeltaV()/(this->fResistivity);
			input->NotifyOnOutput();
			output->NotifyOnInput();
			SetValid(GetDeltaV() == this->fCurrent * this->fResistivity );
		}
	}

	void WComponent::ACUpdate(double timeStep, double timeToGo){
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
			DCUpdate();
		}
	}
	void WComponent::NotifyOnInput(){
		if(n_iterations++ >max_iterations) return;
		if(!output) this->output = new WConnection();

		SetValid(GetDeltaV() == this->fCurrent * this->fResistivity );

		if( !IsValid() ){	
			this->fCurrent = GetDeltaV()/(this->fResistivity);
			output->NotifyOnInput();
		}
	}
	void WComponent::NotifyOnOutput(){
		if(n_iterations++ >max_iterations) return;
		if(!input) this->input = new WConnection();

		SetValid(GetDeltaV() == this->fCurrent * this->fResistivity );

		if( !IsValid() ){		
			this->fCurrent = GetDeltaV()/(this->fResistivity);
			input->NotifyOnOutput();
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
}