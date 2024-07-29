#ifndef QUAD_HPP
#define QUAD_HPP

#include <cmath>

#include <memory>

#include "utils.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "material.hpp"
#include "aabb.hpp"
#include "ray.hpp"
#include "interval.hpp"

class Planar : public Hittable
{
  private:
	Point3 plane_orig;
	Vec3 u;
	Vec3 v;
	std::shared_ptr<Material> material;
	AABB bbox;
	Vec3 normal;
	double coeff_D;
	Vec3 pr_coeff;

  public:
	Planar(	const Point3 &_plane_orig
			, const Vec3 &_u
			, const Vec3 &_v
			, std::shared_ptr<Material> _material):
		plane_orig(_plane_orig)
		, u(_u)
		, v(_v)
		, material(_material)
	{
		Vec3 uv_cross = cross(u, v);
		normal        = unit_vector(uv_cross);
		coeff_D       = dot(normal, plane_orig);

		pr_coeff      = uv_cross / dot(uv_cross, uv_cross);

		set_bound_box();
	}

	virtual void set_bound_box()
	{
		AABB main_diag_bbox      = AABB(plane_orig + u, plane_orig + v);
		AABB secondary_diag_bbox = AABB(plane_orig, plane_orig + u + v);

		bbox = AABB(main_diag_bbox, secondary_diag_bbox);
	}

	AABB bounding_box() const override { return bbox; }

	bool hit(	const Ray &ray
						, Interval interval
						, Hit_record &record) const override
	{
		double denom = dot(normal, ray.direction());

		if(cmp_double(fabs(denom), 0) == 0) return false;

		double hit_coeff = (coeff_D - dot(normal, ray.origin())) / denom;

		if(!interval.contains(hit_coeff)) return false;

		Point3 intersection = ray.at(hit_coeff);

		Vec3 plane_orig_to_inter = intersection - plane_orig;
		double coeff_u       = dot(pr_coeff, cross(plane_orig_to_inter, v));
		double coeff_v       = dot(pr_coeff, cross(u, plane_orig_to_inter));

		if(!is_inside(coeff_u, coeff_v, record)) return false;

		record.ray_coeff = hit_coeff;
		record.hit_point = intersection;
		record.material  = material;

		record.set_against_ray(ray, normal);

		return true;
	}

	virtual bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const = 0;
};

class Quad : public Planar
{
  public:
	using Planar::Planar;

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override
	{
		Interval unit_inter(0, 1);

		if(!unit_inter.contains(coeff_u) || !unit_inter.contains(coeff_v))
		{
			return false;
		}

		record.u = coeff_u;
		record.v = coeff_v;

		return true;
	}
};

class Disk : public Planar
{
  private:
	double radius;

  public:
	Disk(	const Point3 &_plane_orig
			, const Vec3 &_u
			, const Vec3 &_v
			, std::shared_ptr<Material> _material
			, double _radius):
		Planar(_plane_orig, _u, _v, _material), radius(_radius) {}

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override
	{
		if(!(std::sqrt(coeff_u * coeff_u + coeff_v * coeff_v) < radius))
		{
			return false;
		}

		record.u = coeff_u;
		record.v = coeff_v;

		return true;
	}
};

class Triangle : public Planar
{
  public:
	using Planar::Planar;

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override
	{
		if(!(coeff_u > 0 && coeff_v > 0 && coeff_u + coeff_v < 1))
		{
			return false;
		}

		record.u = coeff_u;
		record.v = coeff_v;

		return true;
	}
};

#endif
