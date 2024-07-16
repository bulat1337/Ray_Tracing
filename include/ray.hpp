#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray
{
private:
	Point3 orig;
	Vec3   dir;
public:
	Ray() = default;
	Ray(const Ray &other) = default;

	Ray(const Point3 &set_orig, const Vec3 &set_dir):
		orig(set_orig),
		dir(set_dir) {}

	const Point3 &origin() const
	{
		return orig;
	}

	const Vec3 &direction() const
	{
		return dir;
	}

	Point3 at(double coeff) const
	{
		return orig + coeff * dir;
	}
};

#endif
