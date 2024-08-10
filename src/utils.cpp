#include "utils.h"

#include <cmath>
#include <cstdlib>

#include <limits>
#include <chrono>
#include <iostream>

int cmp_double(double first_double, double second_double)
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

double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

double rand_double()
{
	return rand() / (RAND_MAX + 1.0);
}

double rand_double(double min, double max)
{
	return min + (max - min) * rand_double();
}

int rand_int(double min, double max)
{
	return static_cast<int>(rand_double(min, max + 1));
}


Time_guard::Time_guard():
	start(clock::now()) {}

Time_guard::~Time_guard()
{
	time_point end = clock::now();

	std::chrono::duration<double> duration = end - start;

	overall_time += duration;

	std::clog << "Passed time:\t" << overall_time.count() << " seconds" << std::endl;
	std::clog << "Row time:\t" << duration.count() << " seconds" << std::endl << '\n';
}

std::chrono::duration<double> Time_guard::overall_time = std::chrono::duration<double>(0);
