#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <limits>
#include <cstdlib>
#include <chrono>

const double infinity 	= std::numeric_limits<double>::infinity();
const double pi			= 3.141'592'653'589'793'238'462;

int cmp_double(double first_double, double second_double);

double degrees_to_radians(double degrees);

double rand_double();

double rand_double(double min, double max);

int rand_int(double min, double max);

class Time_guard
{
	using clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::time_point<clock>;

  private:
	time_point start;

  public:
	static std::chrono::duration<double> overall_time;

	Time_guard();

	~Time_guard();
};

#endif
