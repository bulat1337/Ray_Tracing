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

	static const Interval empty;
	static const Interval universe;
};

const Interval Interval::empty 		= Interval(+infinity, -infinity);
const Interval Interval::universe 	= Interval(-infinity, +infinity);

#endif
