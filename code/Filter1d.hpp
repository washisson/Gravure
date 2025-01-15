#ifndef _Filter1d
#define _Filter1d
#include <math.h>
#include "Interfaces.hpp"
#include "Constants.hpp"

class Filter1d: public Filter1dInterface{
protected:
	int size, radius;
	float *kernel;
public:
	Filter1d(): kernel(nullptr), size(0){}
	~Filter1d(){
		if(kernel!= nullptr)
			delete[] kernel;
	}

	int getSize() const override{
		return size;
	}

	int getRadius() const override{
		return radius;
	}

	const float* getKernel() const override{
		return kernel;
	}
};

class GaussianFilter1d: public Filter1d{
public:
	// GaussianFilter1d(): Filter1d;
	// ~GaussianFilter1d();
	GaussianFilter1d(float sigma){
		float sum = 0;

		radius = ceil(sigma * SIGMA_RADIUS_COEF);
		size = radius * 2 + 1;
		kernel = new float[size];

		for(int i = - radius; i <= radius; ++ i)
			sum += kernel[i + radius] = exp(-(i * i) / (2 * sigma * sigma));

		for(int i = 0; i < size; ++ i)
			kernel[i] /= sum;
	}
};

#endif