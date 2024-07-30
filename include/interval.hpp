#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "utils.hpp"

class Interval
{
public:
	double min = 0.0;
	double max = 0.0;

	Interval():
		min(+infinity),
		max(-infinity) {}

	Interval(double set_min, double set_max):
		min(set_min),
		max(set_max) {}

	Interval(const Interval &inter_1, const Interval &inter_2):
		min(fmin(inter_1.min, inter_2.min))
		, max(fmax(inter_1.max, inter_2.max)) {}

	double size() const
	{
		return max - min;
	}

	bool contains(double num) const
	{
		return min <= num && num <= max;
	}

	bool surrounds(double num) const
	{
		return min < num && num < max;
	}

	double clamp(double num) const
	{
		if(num > max) return max;

		if(num < min) return min;

		return num;
	}

	Interval expand(double delta) const
	{
		return Interval(min - delta / 2, max + delta + 2);
	}

	static const Interval empty;
	static const Interval universe;
};

const Interval Interval::empty 		= Interval(+infinity, -infinity);
const Interval Interval::universe 	= Interval(-infinity, +infinity);

Interval operator + (const Interval &interval, double offset)
{
	return Interval(interval.min + offset, interval.max + offset);
}

Interval operator + (double offset, const Interval &interval)
{
	return interval + offset;
}

#endif
