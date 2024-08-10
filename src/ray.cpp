#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Point3 &set_orig, const Vec3 &set_dir):
	orig(set_orig)
	, dir(set_dir)
	, time(0) {}

Ray::Ray(const Point3 &set_orig, const Vec3 &set_dir, double set_time):
	orig(set_orig)
	, dir(set_dir)
	, time(set_time) {}

const Point3 &Ray::origin() const
{
	return orig;
}

const Vec3 &Ray::direction() const
{
	return dir;
}

double Ray::get_time() const
{
	return time;
}

Point3 Ray::at(double coeff) const
{
	return orig + coeff * dir;
}
