#ifndef WElement_h_
#define WElement_h_

namespace Wiers{

	class WElement{
		bool valid;//<!Set this flag
		static unsigned int count;
		unsigned int id;
	protected:
		static unsigned int decimal_places;
		static unsigned int n_iterations;
		static unsigned int max_iterations;
		static double fGlobalTime;
		static double fCurrentTimeStep;

	public:
		WElement() : valid(false), id(++count){}
		bool IsValid() const {return valid;}
		void SetValid(bool x){valid = x;}
		unsigned int GetID(){return this->id;}

		virtual void DCUpdate()=0;
		virtual void NotifyOnInput()=0;
		virtual void NotifyOnOutput()=0;

		//There are the AC Components
		virtual void ACUpdate(double timeStep, double TimeToGo)=0;
		virtual void CheckACInput()=0;
		virtual void CheckACOutput()=0;

		virtual void UpdateACInput()=0;
		virtual void UpdateACOutput()=0;
	};

}



#endif //WElement_h_