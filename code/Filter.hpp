#ifndef _Filter
#define _Filter

#include "Interfaces.hpp"
#include "Constants.hpp"
#include "cmath"

class SeparateFilter: public StaticFilterInterface <SeparateFilter>{
public:
	static float convertImp(float x){
		if(x < 0.5)
			return 0;
		return 1;
	}
};

class HorizontalSinLinesPattern:public FilterInterface{
	double t, q;
	double max_res = 1, min_res = -1;
public:
	HorizontalSinLinesPattern():FilterInterface::FilterInterface(0, 0){}
	HorizontalSinLinesPattern(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;

		res = std::sin(y);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class HorizontalSinLinesPattern_sd:public FilterInterface{
	double t, q;
	double max_res = 1, min_res = -1;
public:
	HorizontalSinLinesPattern_sd():FilterInterface::FilterInterface(0, 0){}
	HorizontalSinLinesPattern_sd(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double x1, y1;
		double res;
		double d = val * my_pi/2 / 4;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;
		x1 = std::cos(d) * x - std::sin(d) * y;
		y1 = std::sin(d) * x + std::cos(d) * y;

		res = std::sin(y1);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class VerticalSinLinesPattern:public FilterInterface{
	double t, q;
	double max_res = 1, min_res = -1;
public:
	VerticalSinLinesPattern():FilterInterface::FilterInterface(0, 0){}
	VerticalSinLinesPattern(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;

		res = std::sin(x);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class OffsetPattern:public FilterInterface{
	double t, q;
	double max_res = 2, min_res = -2;
public:
	OffsetPattern():FilterInterface::FilterInterface(0, 0){}
	OffsetPattern(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;

		res = std::sin(x + y) + std::sin(x - y);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class OffsetPattern_sd:public FilterInterface{
	double t, q;
	double max_res = 2, min_res = -2;
public:
	OffsetPattern_sd():FilterInterface::FilterInterface(0, 0){}
	OffsetPattern_sd(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q + val * 8, y = (j - height * .5 + 0.5l) * q + 12 * val;

		res = std::sin(x + y) + std::sin(x - y);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class OffsetPattern_sd2:public FilterInterface{
	double t, q;
	double max_res = 2, min_res = -2;
public:
	OffsetPattern_sd2():FilterInterface::FilterInterface(0, 0){}
	OffsetPattern_sd2(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double x1, y1;
		double res;
		double d = val * my_pi / 2;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;
		x1 = std::cos(d) * x - std::sin(d) * y;
		y1 = std::sin(d) * x + std::cos(d) * y;

		res = std::sin(y1);

		res = std::sin(x1 + y1) + std::sin(x1 - y1);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};


class KletkaPattern:public FilterInterface{
	double t, q;
	double max_res = 2, min_res = -2;
public:
	KletkaPattern():FilterInterface::FilterInterface(0, 0){}
	KletkaPattern(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q, y = (j - height * .5 + 0.5l) * q;

		res = sin(x + y + sin(x + y) * my_pi) + sin(x - y + sin(x - y) * my_pi);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

class KletkaPattern_sd:public FilterInterface{
	double t, q;
	double max_res = 2, min_res = -2;
public:
	KletkaPattern_sd():FilterInterface::FilterInterface(0, 0){}
	KletkaPattern_sd(int w, int h, double temp_t): FilterInterface::FilterInterface(w, h), t(temp_t){
		q = 2 * my_pi / t;
	}

	float convert(const int i, const int j, const float val) const override{
		double x, y;
		double res;

		x = (i - width * .5 + 0.5l) * q + val * 8, y = (j - height * .5 + 0.5l) * q + val * 12;

		res = sin(x + y + sin(x + y) * my_pi) + sin(x - y + sin(x - y) * my_pi);
		res = (res - min_res) / (max_res - min_res);

		return res;
	}
};

#endif
