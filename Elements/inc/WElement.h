#ifndef WElement_h_
#define WElement_h_

namespace Wiers{

	class WElementVisitor;
	class WElement{
		bool valid;//<!Set this flag
		static unsigned int count;
		unsigned int id;
	protected:
		static unsigned int decimal_places;
		unsigned int n_iterations;
		static unsigned int max_iterations;
		static long double fGlobalTime;
		static long double fCurrentTimeStep;

	public:
		WElement() : valid(false), id(++count), n_iterations(0){}
		virtual bool IsValid()=0;
		void SetValid(bool x){valid = x;}
		unsigned int GetID(){return this->id;}

		//There are the AC Components
		virtual void ACUpdate(long double timeStep, long double TimeToGo)=0;
		virtual void CheckACInput()=0;
		virtual void CheckACOutput()=0;

		virtual void UpdateACInput()=0;
		virtual void UpdateACOutput()=0;

		//This is for the visitor pattern
		virtual void UpdateWithVisitor()=0;//Starts the whole process
		virtual void AcceptVisitorUpstream(WElementVisitor*)=0;
		virtual void AcceptVisitorDownStream(WElementVisitor*)=0;

	};

}



#endif //WElement_h_