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
		long double fVoltage;//<! The voltage relative to the global ground
		long double fACVoltage;
		long double fReactance;

		static long double fACVoltageMax;

	public:
		WConnection(long double voltage=0.0, long double reactance=0.0) : fVoltage(voltage), 
			fReactance(reactance), fACVoltage(0.0) {}

		virtual bool IsValid();

		void SetInput(WComponent* const );
		void SetOutput(WComponent* const );
		std::vector<WComponent*> GetInputs(){return inputs;}
		std::vector<WComponent*> GetOutputs(){return outputs;}

		long double GetVoltage() const {return this->fVoltage;}
		long double GetACVoltage() const {return this->fACVoltage;}
		virtual long double GetInputCurrent();
		virtual long double GetOutputCurrent();
		virtual long double GetTotalCurrent();
		virtual long double GetInputImpedance();
		virtual long double GetOutputImpedance();
		virtual long double GetVoltageDifference();


		virtual void ACUpdate(long double timeStep, long double TimeToGo);
		virtual long double GetTotalACCurrent();
		virtual void CheckACInput();
		virtual void CheckACOutput();

		virtual void UpdateACInput();
		virtual void UpdateACOutput();

		void UpdateWithVisitor();
		void AcceptVisitorUpstream(WElementVisitor*);
		void AcceptVisitorDownStream(WElementVisitor*);
	
	protected:
		void SetVoltage(long double x){this->fVoltage = x;}
	};
}

#endif //WConnection_h_