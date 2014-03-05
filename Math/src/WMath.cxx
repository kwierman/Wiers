namespace Wiers{

	static double accuracy = 0.0023;

	bool isEqual(const double& first, const double& second){
		if(first<second){
			return (first+accuracy ) >= second;
		}
		return second+accuracy >= first;
	}

	double round(const double& first, const int& nDigits ){
		double rounded = first;
		for(int i=0;i<nDigits;i++) rounded*=10.0;
		rounded = int(rounded);
		for(int i=0;i<nDigits;i++) rounded/=10.0;
		return rounded;
	}
}