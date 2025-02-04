#ifndef _Interfaces
#define _Interfaces

template <typename StaticFilterDerived>
class StaticFilterInterface{
public:
	static float convert (float x){
		return StaticFilterDerived::convertImp(x);
	}
};

class FilterInterface{
protected:
	int width, height;
public:
	FilterInterface(int w, int h): width(w), height(h){}
	virtual ~FilterInterface(){}

	virtual float convert(const int i, const int j, const float val) const{
		return 0.8;
	}

};

class Filter1dInterface{
public:
	// Filter1dInterface();
	virtual ~Filter1dInterface() {}
	virtual int getRadius() const = 0;
	virtual int getSize() const = 0;
	virtual const float* getKernel() const =0;
};

class Filter2dInterface{
public:
	// Filter2dInterface();
	virtual ~Filter2dInterface() {}
	virtual int getRadius() const = 0;
	virtual const float* const* getKernel() const =0;
};

class ColorMapInterface{
public:
	// ColorMapInterface();
	// ~ColorMapInterface();
	
};

#endif