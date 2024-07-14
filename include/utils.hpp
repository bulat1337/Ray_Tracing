#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

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

#endif
