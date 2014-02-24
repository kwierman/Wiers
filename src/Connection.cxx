#include "Connection.h"
#include "Component.h"

namespace Wiers{
	void Connection::NotifyNewCurrentOnInput(double x){
		for(cIt it = outputs.begin(); it!= outputs.end();++it ){
			double voltage = (*it)->SetNewCurrent(x/double(outputs.size() ));
		}

		//based off all the inputs, let's get a reading of the voltage
	}
	void Connection::NotifyNewCurrentOnOutput(double x ){

	}

}