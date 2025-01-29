#ifndef _Filter
#define _Filter

#include "Interfaces.hpp"

class SeparateFilter: public StaticFilterInerface <SeparateFilter>{
public:
	static float convertImp(float x){
		if(x < 0.5)
			return 0;
		return 1;
	}
};

#endif
