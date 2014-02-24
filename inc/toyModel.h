namespace Wiers{

	struct Connection;
	struct Component{
		double impedance;
		double current;
		Connection* input;
		Connection* output;
	};
	struct Connection{
		double voltage;
		Component* input;
		Component* output;
	};


}