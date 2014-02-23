#ifndef Resistor_h_
#define Resistor_h_

#include "Component.h"

namespace Wiers{

	class Resistor : public Component{
		double voltage;
		double current;
		double resistance;

	public:
		Resistor(double x) : resistance(x), voltage(0.0),current(0.0){}

		double GetVoltage(){

			double totalImpedance = this->resistance + input->GetOutputImpedance() + output->GetInputImpedance();

			double totalVoltage = this->input->GetInputVoltage() - this->output->GetOutputVoltage();

			double current = totalVoltage/totalImpedance;
			return this->resistance * current;

		}

		double GetInputImpedance(){
			return this->resistance+this->output->GetInputImpedance();
		}
		double GetOutputImpedance(){
			return this->resistance+ this->input->GetOutputImpedance();
		}

		double GetInputVoltage(){
			return this->input->GetInputVoltage();
		}
		double GetOutputVoltage(){
			return this->output->GetOutputVoltage();
		}

	};
}


#endif //Resistor_h_