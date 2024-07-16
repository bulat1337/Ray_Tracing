#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <limits>
#include <cstdlib>

const double infinity 	= std::numeric_limits<double>::infinity();
const double pi			= 3.141'592'653'589'793'238'462;

inline int cmp_double(double first_double, double second_double)
{
    const double eps = 1e-10;

    if(isnan(first_double) && isnan(second_double))
    {
        return 0;
    }
    if (fabs(first_double - second_double) < eps)
    {
        return 0;
    }
    else if ((first_double - second_double) > eps)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double get_random()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double get_random(double min, double max)
{
	return min + (max - min) * get_random();
}

#endif
