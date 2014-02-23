#ifndef Component_h_
#define Component_h_

namespace Wiers{
	class Component{
	protected:
		Component* input;
		Component* output;

	public:
		void SetInput(Component* other){
			this->input = other;
		}
		void SetOutput(Component* other){
			this->output = other;
		}

		virtual double GetInputImpedance()=0;
		virtual double GetOutputImpedance()=0;
		virtual double GetInputVoltage()=0;
		virtual double GetOutputVoltage()=0;
	};
}
#endif //Component_h_