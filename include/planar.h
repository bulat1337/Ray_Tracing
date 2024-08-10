#ifndef QUAD_HPP
#define QUAD_HPP

#include <cmath>

#include <memory>

#include "utils.h"
#include "hittable.h"
#include "vec3.h"
#include "material.h"
#include "aabb.h"
#include "ray.h"
#include "interval.h"
#include "hittables.h"

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
			, std::shared_ptr<Material> _material);

	virtual void set_bound_box();

	AABB bounding_box() const override;

	bool hit(	const Ray &ray
						, Interval interval
						, Hit_record &record) const override;

	virtual bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const = 0;
};

class Quad : public Planar
{
  public:
	using Planar::Planar;

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override;
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
			, double _radius);

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override;
};

class Triangle : public Planar
{
  public:
	using Planar::Planar;

	bool is_inside(double coeff_u, double coeff_v, Hit_record &record) const override;
};

std::shared_ptr<Hittables> box(	const Point3 &a
								, const Point3 &b
								, std::shared_ptr<Material> material);

#endif
