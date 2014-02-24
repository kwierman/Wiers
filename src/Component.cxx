#include "Component.h"
#include "Connection.h"

namespace Wiers{
	unsigned int Component::count=0;

	void Component::SetInput(Component* other){
		this->input = other->GetOutput();
	}
	void Component::SetOutput(Component* other){
		this->output = other->GetInput();
	}

	Connection* Component::GetInput(){
		if(!input) input = new Connection();
		return input;
	}
	Connection* Component::GetOutput(){
		if(!output) output = new Connection();
		return output;
	}

}