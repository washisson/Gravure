#ifndef _Interfaces
#define _Interfaces

template <typename StaticFilterDerived>
class StaticFilterInerface{
public:
	static float convert (float x){
		return StaticFilterDerived::convertImp(x);
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