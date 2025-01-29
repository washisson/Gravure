#ifndef _ColorMap
#define _ColorMap
#include "Interfaces.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
// #include <iostream>
// #include "Filter2d.hpp"

class ColorMap: public ColorMapInterface{
protected:
	int width, height;
	float **arr;
public:
	ColorMap(): arr(nullptr), width(0), height(0){}

	ColorMap(const sf::Image & im){
		const uint8_t *arr8 = im.getPixelsPtr();

		width = im.getSize().x, height = im.getSize().y;
		if(width * height > 0){
			arr = new float*[width];
			arr[0] = new float[height * width];
			for(int i = 1; i < width; ++ i)
				arr[i] = arr[0] + i * height;

			for(int i = 0; i < width; ++ i)
				for(int j = 0; j < height; ++ j)
					arr[i][j] = arr8[(j * width + i) * 4] * 1. / 255;
		}
		else
			arr = nullptr;
	}

	ColorMap(int w, int h): width(std::max(w, 0)), height(std::max(h, 0)){
		if(width * height > 0){
			arr = new float*[w];
			arr[0] = new float[h * w];
			for(int i = 1; i < w; ++ i)
				arr[i] = arr[0] + i * h;
		}
		else 
			arr = nullptr;
	}

	ColorMap(ColorMap && x): width(x.width), height(x.height) {
		arr = x.arr;
		x.arr = nullptr;
		x.width = 0, x.height = 0;
	}

	ColorMap(const ColorMap & x): ColorMap(x.width, x.height){
		std::cout << arr << '\n';
		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++ j)
				arr[i][j] = x.arr[i][j];
	}

	~ColorMap(){
		if(arr!= nullptr){
			if(arr[0] != nullptr)
				delete[] arr[0];
			delete[] arr;
		}
	}

	ColorMap& operator=(const ColorMap & x){
		if(this != &x){
			if(arr != nullptr){
				if(arr[0] != nullptr)
					delete[] arr[0];
				delete[] arr;
			}
			width = x.width, height = x.height;
			if(width * height > 0 && x.arr != nullptr){
				arr = new float*[width];
				arr[0] = new float[height * width];
				for(int i = 1; i < width; ++ i)
					arr[i] = arr[0] + i * height;

				for(int i = 0; i < width; ++ i)
					for(int j = 0; j < height; ++ j)
						arr[i][j] = x.arr[i][j];
			}
			else
				arr = nullptr;
		}

		// std::cout << "Обычное присвоение для ColorMap\n";

		return *this;
	}

	ColorMap& operator=(ColorMap && x){
		if(this != &x){
			if(arr != nullptr){
				if(arr[0] != nullptr)
					delete[] arr[0];
				delete[] arr;
			}
			arr = x.arr;
			width = x.width, height = x.height;
			x.arr = nullptr;
			x.width = x.height = 0;
		}
		// std::cout << "Присвоение перемещением для ColorMap\n";

		return *this;
	}

	ColorMap operator-(const ColorMap & x) const{
		const int t_width = std::min(width, x.width), t_height = std::min(height, x.height);
		ColorMap tempColorMap(t_width, t_height);

		for(int i = 0; i < t_width; ++ i)
			for(int j = 0; j < t_height; ++ j)
				tempColorMap.arr[i][j] = arr[i][j] - x.arr[i][j];

		return tempColorMap;
	}

	ColorMap operator/(float x) const{
		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++ j)
				tempColorMap.arr[i][j] = arr[i][j] / x;

		return tempColorMap;
	}

	ColorMap operator+(float x) const{
		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++ j)
				tempColorMap.arr[i][j] = arr[i][j] + x;
			
		return tempColorMap;
	}

	sf::Image getWBImage() const{
		sf::Image tempImage;
		if(width * height > 0){
			uint8_t *arr8 = new uint8_t[width * height * 4];

			for(int i = 0; i < width * height; ++ i)
				arr8[i * 4 + 2] = arr8[i * 4 + 1] = arr8[i * 4] = (int)(arr[i % width][i / width] * 255),
				arr8[i * 4 + 3] = 255;

			tempImage.create(width, height, arr8);
		}

		return tempImage;
	}

	sf::Color getPixel(int x, int y) const{
		if(x >= 0 && x < width && y >= 0 && y < height)
			return sf::Color(int (arr[x][y] * 255), int (arr[x][y] * 255), int (arr[x][y] * 255), 255);
		return sf::Color::Yellow;
	}

	template<typename StaticFilterDerived>
	ColorMap useFilter() const{
		ColorMap tempColorMap(width, height);
		// ColorMap tempColorMap(*this);

		for(int i = 0; i < width; ++ i){
			for(int j = 0; j < height; ++j){
				tempColorMap.arr[i][j] = StaticFilterDerived::convert(arr[i][j]);
				// cout << tempColorMap.arr[i][j]
			}
		}

		return tempColorMap;
	}


	ColorMap useHorizontalFilter1d(const Filter1dInterface & filter) const{
		int radius = filter.getRadius();
		const float*  filterKernel = filter.getKernel();

		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++j){
				float sum = 0;

				for(int ki = - radius; ki <= radius; ++ ki)
					sum += arr[std::min(width - 1, std::max(i + ki, 0))][j] * filterKernel[radius + ki];

				tempColorMap.arr[i][j] = sum;
			}
		return tempColorMap;
	}

	ColorMap useVerticalFilter1d(const Filter1dInterface & filter) const{
		int radius = filter.getRadius();
		const float*  filterKernel = filter.getKernel();

		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++j){
				float sum = 0;

				for(int kj = - radius; kj <= radius; ++ kj)
					sum += arr[i][std::min(height - 1, std::max(j + kj, 0))] * filterKernel[radius + kj];

				tempColorMap.arr[i][j] = sum;
			}
		return tempColorMap;
	}

	ColorMap useFilter1d(const Filter1dInterface & filter) const{
		return useHorizontalFilter1d(filter).useVerticalFilter1d(filter);
	}
	ColorMap useFilter2d(const Filter2dInterface & filter) const{
		int radius = filter.getRadius();
		const float* const* filterKernel = filter.getKernel();
		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++ j){
				float sum = 0;

				for(int ki = - radius; ki <= radius; ++ ki)
					for(int kj = -radius; kj <= radius; ++ kj)
						sum += arr[std::min(width - 1, std::max(i + ki, 0))][std::min(height - 1, std::max(j + kj, 0))] * filterKernel[radius  + ki][radius + kj];

				tempColorMap.arr[i][j] = sum;
			}
		return tempColorMap;
	}

	ColorMap linearConvert(const float a, const float b) const{
		ColorMap tempColorMap(width, height);

		for(int i = 0; i < width; ++ i)
			for(int j = 0; j < height; ++ j)
				tempColorMap.arr[i][j] = a * arr[i][j] + b;

		return tempColorMap;
	}

	ColorMap merge(const ColorMap & other, const float alpha){
		int minWidth = std::min(width, other.width),  maxWidth = std::max(width, other.width), minHeight = std::min(height, other.height), maxHeight = std::max(height, other.height);
		ColorMap tempColorMap(maxWidth, maxHeight);

		for(int i = 0; i < minWidth; ++ i)
			for(int j = 0; j < minHeight; ++ j)
				tempColorMap.arr[i][j] = arr[i][j] * (1 - alpha) + other.arr[i][j] * alpha;


		for(int i = minWidth; i < maxWidth; ++ i)
			for(int j = minHeight; j < maxHeight; ++ j)
				tempColorMap.arr[i][j] = 0;

		for(int i = minWidth; i < width; ++ i)
			for(int j = 0; j < height; ++ j)
				tempColorMap.arr[i][j] = arr[i][j];
		for(int i = minWidth; i < other.width; ++ i)
			for(int j = 0; j < other.height; ++ j)
				tempColorMap.arr[i][j] = other.arr[i][j];

		for(int i = 0; i < minWidth; ++ i)
			for(int j = minHeight; j < height; ++ j)
				tempColorMap.arr[i][j] = arr[i][j];
		for(int i = 0; i < minWidth; ++ i)
			for(int j = minHeight; j < other.height; ++ j)
				tempColorMap.arr[i][j] = other.arr[i][j];

		return tempColorMap;
	}
};

#endif