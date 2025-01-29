#ifndef _Filter2d
#define _Filter2d
#include <math.h>
#include "Interfaces.hpp"
#include "Constants.hpp"

class Filter2d: public Filter2dInterface{
protected:
	int width, height, radius;
	float **kernel;

public:
	Filter2d(): kernel(nullptr), width(0), height(0), radius(0){}

	~Filter2d(){
		if(kernel!= nullptr){
			if(kernel[0] != nullptr)
				delete[] kernel[0];
			delete[] kernel;
		}
	}

	int getRadius() const override{
		return radius;
	}

	const float* const* getKernel() const override{
		return kernel;
	}
};

class GaussianFilter2d: public Filter2d{
public:

	GaussianFilter2d(float sigma) {
		float sum = 0;

		radius = ceil(sigma * SIGMA_RADIUS_COEF);
		width = height = radius * 2 + 1;
		kernel = new float*[width];
		kernel[0] = new float[height * width];
		for(int i = 1; i < width; ++ i)
			kernel[i] = kernel[0] + i * height;

		// Вычисляем ядро Гаусса
	    for (int i = -radius; i <= radius; i++) {
	        for (int j = -radius; j <= radius; j++) {
	            kernel[i + radius][j + radius] = exp(-(i * i + j * j) / (2 * sigma * sigma));
	            sum += kernel[i + radius][j + radius];
	        }
	    }

	    // Нормализация ядра
	    for (int i = 0; i < width; i++)
	        for (int j = 0; j < height; j++)
	            kernel[i][j] /= sum;
	}

};

#endif