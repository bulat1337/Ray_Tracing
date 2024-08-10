#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.h"

class Ray
{
  private:
	Point3 orig;
	Vec3   dir;
	double time;
  public:
	Ray();

	Ray(const Point3 &set_orig, const Vec3 &set_dir);

	Ray(const Point3 &set_orig, const Vec3 &set_dir, double set_time);

	const Point3 &origin() const;

	const Vec3 &direction() const;

	double get_time() const;

	Point3 at(double coeff) const;
};

#endif
