#include "interval.h"

Interval::Interval():
	min(+infinity),
	max(-infinity) {}

Interval::Interval(double set_min, double set_max):
	min(set_min),
	max(set_max) {}

Interval::Interval(const Interval &inter_1, const Interval &inter_2):
	min(fmin(inter_1.min, inter_2.min))
	, max(fmax(inter_1.max, inter_2.max)) {}

double Interval::size() const
{
	return max - min;
}

bool Interval::contains(double num) const
{
	return min <= num && num <= max;
}

bool Interval::surrounds(double num) const
{
	return min < num && num < max;
}

double Interval::clamp(double num) const
{
	if(num > max) return max;

	if(num < min) return min;

	return num;
}

Interval Interval::expand(double delta) const
{
	return Interval(min - delta / 2, max + delta / 2);
}

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
