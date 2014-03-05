#ifndef WComponent_h_
#define WComponent_h_

#include "WElement.h"

namespace Wiers{

	class WConnection;

	class WComponent : public WElement{

		WConnection* input;
		WConnection* output;

		double fResistivity;//<! This is the DC impedance of the component.
		double fReactance;

		double fCurrent;//<! This is the DC current of the component
		double fACCurrent;
		static double fACCurrentMax;

	public:
		WComponent(double resistivity=1.0, double reactance=0.0) : fResistivity(resistivity), 
			fCurrent(0.0), input(0), output(0), fReactance(reactance), fACCurrent(0.0) {}
		
		virtual double GetImpedance() const {return fResistivity;}
		virtual double GetCurrent() const {return fCurrent;}
		virtual double GetACCurrent() const {return fACCurrent;}
		virtual double GetDeltaV();
		
		virtual void DCUpdate();
		
		virtual void NotifyOnInput();
		virtual void NotifyOnOutput();

		virtual void SetInput(WConnection*);
		virtual void SetOutput(WConnection*);

		WConnection* GetInput();
		WConnection* GetOutput();
		
		virtual void ACUpdate(double timeStep, double TimeToGo);
		virtual void CheckACInput();
		virtual void CheckACOutput();

		virtual void UpdateACInput();
		virtual void UpdateACOutput();

		virtual double GetDeltaACV();

	protected:
		void SetImpedance(double x){this->fResistivity = x;}
		void SetCurrent(double x){this->fCurrent=x;} 
	};
}

#endif //WComponent_h_