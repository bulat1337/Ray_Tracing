#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <memory>

#include "ray.hpp"
#include "interval.hpp"

class Material;

struct Hit_record
{
	Point3 hit_point;
	Vec3 sur_normal;
	double ray_coeff;
	bool front_faced;
	std::shared_ptr<Material> material;

	void set_against_ray(const Ray &ray, const Vec3 &out_normal)
	{
		// NOTE: out_normal is assumed to have unit length
		front_faced = dot(out_normal, ray.direction()) < 0;

		sur_normal = front_faced ? out_normal : - out_normal;
	}
};

class Hittable
{
public:
	virtual bool hit(	const Ray &ray
						, Interval interval
						, Hit_record &record) const = 0;

	virtual ~Hittable() = default;
};



#endif
