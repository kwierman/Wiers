#ifndef Rail_h_
#define Rail_h_

namespace Wiers{

	class Rail : public Component{
		double voltage;

	public:
		Rail(double x) : voltage(x) {}
	};
}

#endif //Rail_h_