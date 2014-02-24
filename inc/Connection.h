#ifndef Connection_h_
#define Connection_h_

//#include <vector>
#include <iostream>

namespace Wiers{
	class Component;

	class Connection{
	protected:
		double voltage;
		Component* input;
		Component* output;
		//typedef std::vector<Component*>::iterator cIt;
	public:
		Connection() : input(0) , output(0) {}
		double GetVoltage(){return voltage;}
		virtual bool ChangeVoltage(double x){
			std::cout<<"Attempting to change voltage by: "<<x<<std::endl;
			double ratio = output->resistance==0 ?0: input->resistance/output->resistance;

			voltage += x*ratio;
			return true;
		}
	};

}

#endif //Connection_h_