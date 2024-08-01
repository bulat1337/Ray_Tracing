#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray
{
  private:
	Point3 orig;
	Vec3   dir;
	double time;
  public:
	Ray() = default;

	Ray(const Point3 &set_orig, const Vec3 &set_dir):
		orig(set_orig)
		, dir(set_dir)
		, time(0) {}

	Ray(const Point3 &set_orig, const Vec3 &set_dir, double set_time):
		orig(set_orig)
		, dir(set_dir)
		, time(set_time) {}

	const Point3 &origin() const
	{
		return orig;
	}

	const Vec3 &direction() const
	{
		return dir;
	}

	double get_time() const
	{
		return time;
	}

	Point3 at(double coeff) const
	{
		return orig + coeff * dir;
	}
};

#endif
