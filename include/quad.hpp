#ifndef QUAD_HPP
#define QUAD_HPP

#include <memory>

#include "utils.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "material.hpp"
#include "aabb.hpp"
#include "ray.hpp"
#include "interval.hpp"

class Quad : public Hittable
{
  private:
	Point3 corner;
	Vec3 u;
	Vec3 v;
	std::shared_ptr<Material> material;
	AABB bbox;
	Vec3 normal;
	double coeff_D;

  public:
	Quad(	const Point3 *_corner
			, const Vec3 &_u
			, const Vec3 &_v
			, std::shared_ptr<Material> _material):
		corner(_corner)
		, u(_u)
		, v(_v)
		, material(_material)
	{
		normal  = unit_vector(cross(u, v));
		coeff_D = dot(normal, corner);


		set_bound_box();
	}

	virtual set_bound_box()
	{
		AABB main_diag_bbox      = AABB(corner + u, corner + v);
		AABB secondary_diag_bbox = AABB(corner, corner + u + v);

		bbox = AABB(main_diag_bbox, secondary_diag_bbox);
	}

	AABB bounding_box() const override
	{
		return bbox;
	}

	bool hit(const Ray &ray, const Interval &interval, Hit_record &record)
	{
		double denom = dot(normal, ray.direction());

		if(cmp_double(denom, 0) < 0) return false;

		double hit_coeff = (coeff_D - dot(normal, ray.origin())) / denom;

		if(!interval.contains(hit_coeff)) return false;

		Point3 intersection = ray.at(hit_coeff);

		record.ray_coeff = hit_coeff;
		record.hit_point = intersection;
		record.material  = material;

		record.set_against_ray(ray, normal);

		return true;
	}




}

#endif
