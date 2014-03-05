#include "WElement.h"

namespace Wiers{
	unsigned int WElement::count =0;
	unsigned int WElement::decimal_places = 20;
	unsigned int WElement::n_iterations=0;
	unsigned int WElement::max_iterations=1000000;

	double WElement::fGlobalTime=0.0;//<! The Global Time starts out at 0.0;
	double WElement::fCurrentTimeStep=0.1;//This is to be used to iterate up the time step.

}