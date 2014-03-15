#ifndef WComponent_h_
#define WComponent_h_

#include "WElement.h"

namespace Wiers{

	class WConnection;

	class WComponent : public WElement{

		WConnection* input;
		WConnection* output;

		long double fResistivity;//<! This is the DC impedance of the component.
		long double fReactance;

		long double fCurrent;//<! This is the DC current of the component
		long double fACCurrent;
		static long double fACCurrentMax;

	public:
		WComponent(long double resistivity=1.0, long double reactance=0.0) : fResistivity(resistivity), 
			fCurrent(0.0), input(0), output(0), fReactance(reactance), fACCurrent(0.0) {}

		virtual bool IsValid();
		
		virtual long double GetImpedance() const {return fResistivity;}
		virtual long double GetCurrent() const {return fCurrent;}
		virtual long double GetACCurrent() const {return fACCurrent;}
		virtual long double GetDeltaV();

		virtual void SetInput(WConnection*);
		virtual void SetOutput(WConnection*);

		WConnection* GetInput();
		WConnection* GetOutput();
		
		virtual void ACUpdate(long double timeStep, long double TimeToGo);
		virtual void CheckACInput();
		virtual void CheckACOutput();

		virtual void UpdateACInput();
		virtual void UpdateACOutput();

		virtual long double GetDeltaACV();

		void UpdateWithVisitor();
		void AcceptVisitorUpstream(WElementVisitor*);
		void AcceptVisitorDownStream(WElementVisitor*);

	protected:
		void SetImpedance(long double x){this->fResistivity = x;}
		void SetCurrent(long double x){this->fCurrent=x;} 
	};
}

#endif //WComponent_h_