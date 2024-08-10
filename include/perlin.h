#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <cmath>

#include <algorithm>
#include <memory>

#include "utils.h"
#include "vec3.h"

class Perlin
{
  public:
	Perlin();

	Perlin(const Perlin &other)				 = delete;
	Perlin &operator = (const Perlin &other) = delete;

	double noise(const Point3 &point) const;

	double turbulence(const Point3 &point, int depth) const;

  private:
	static const int          point_count;
	std::unique_ptr<int[]>    perm_x;
	std::unique_ptr<int[]>    perm_y;
	std::unique_ptr<int[]>    perm_z;
	std::unique_ptr<Vec3[]>   rand_vec;

	static std::unique_ptr<int[]> perlin_gen_perm();

	static void permute(int *perm);

	static double perlin_interp(	 const Vec3 c[2][2][2]
									, double frac_portion_x
									, double frac_portion_y
									, double frac_portion_z);
};


#endif // PERLIN_H
