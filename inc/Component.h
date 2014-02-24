#ifndef Component_h_
#define Component_h_


namespace Wiers{
	class Connection;//<! For the connections between other components

	class Component{
		static unsigned int count;
		unsigned int id;
	protected:
		Connection* input;
		Connection* output;
		double resistance;
		double current;

	public:
		Component(double x) : input(0), output(0), resistance(x){ id=count++; }

		unsigned int GetID(){return this->id;}

		void SetInput(Connection* other);
		void SetOutput(Connection* other);

		Connection* GetInput();
		Connection* GetOutput();

		double GetDeltaV();

		virtual void Update();
	};

}
#endif //Component_h_