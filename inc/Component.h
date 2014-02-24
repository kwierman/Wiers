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

	public:
		Component() : input(0), output(0){id=count++;}

		unsigned int GetID(){return this->id;}

		void SetInput(Component* other);
		void SetOutput(Component* other);

		Connection* GetInput();
		Connection* GetOutput();

		virtual void Update()=0;
	};

}
#endif //Component_h_