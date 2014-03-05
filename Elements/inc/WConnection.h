#ifndef WConnection_h_
#define WConnection_h_

#include "WElement.h"
#include "WComponent.h"

#include <vector>

namespace Wiers{

	class WConnection : public WElement {
		std::vector<WComponent*> inputs;
		std::vector<WComponent*> outputs;
		typedef std::vector<WComponent*>::iterator comp_it;
		double fVoltage;//<! The voltage relative to the global ground
		double fACVoltage;
		double fReactance;

		static double fACVoltageMax;

	public:
		WConnection(double voltage=0.0, double reactance=0.0) : fVoltage(voltage), 
			fReactance(reactance), fACVoltage(0.0) {}

		void SetInput(WComponent* const );
		void SetOutput(WComponent* const );
		std::vector<WComponent*> GetInputs(){return inputs;}
		std::vector<WComponent*> GetOutputs(){return outputs;}

		double GetVoltage() const{return this->fVoltage;}
		double GetACVoltage() const {return this->fACVoltage;}
		virtual double GetInputCurrent();
		virtual double GetOutputCurrent();
		virtual double GetTotalCurrent();
		virtual double GetInputImpedance();
		virtual double GetOutputImpedance();
		virtual double GetVoltageDifference();

		virtual void DCUpdate();

		virtual void NotifyOnInput();
		virtual void NotifyOnOutput();

		virtual void ACUpdate(double timeStep, double TimeToGo);
		virtual double GetTotalACCurrent();
		virtual void CheckACInput();
		virtual void CheckACOutput();

		virtual void UpdateACInput();
		virtual void UpdateACOutput();
	
	protected:
		void SetVoltage(double x){this->fVoltage = x;}
	};
}

#endif //WConnection_h_