#ifndef AABB_HPP
#define AABB_HPP

#include "utils.h"
#include "interval.h"
#include "vec3.h"
#include "ray.h"

class AABB
{
  public:
	static const AABB empty;
	static const AABB universe;

	Interval x;
	Interval y;
	Interval z;

	AABB();

	AABB(const Interval &_x, const Interval &_y, const Interval &_z);
	AABB(const Point3 &p_1, const Point3 &p_2);

	AABB(const AABB &box_1, const AABB &box_2);

	Interval axis_interval(size_t id) const;

	bool hit(	const Ray &ray, Interval interval) const;

	int longest_axis() const;

  private:
	void pad_to_mins();
};

AABB operator + (const AABB &bbox, const Vec3 &offset);
AABB operator + (const Vec3 &offset, const AABB &bbox);

#endif
