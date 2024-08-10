#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "utils.h"

class Interval
{
  public:
	double min = 0.0;
	double max = 0.0;

	Interval();

	Interval(double set_min, double set_max);

	Interval(const Interval &inter_1, const Interval &inter_2);

	double size() const;

	bool contains(double num) const;

	bool surrounds(double num) const;

	double clamp(double num) const;

	Interval expand(double delta) const;

	static const Interval empty;
	static const Interval universe;
};

Interval operator +(const Interval &interval, double offset);

Interval operator +(double offset, const Interval &interval);

#endif
