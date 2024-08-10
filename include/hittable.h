#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <memory>

#include "ray.h"
#include "interval.h"
#include "aabb.h"

class Material;

struct Hit_record
{
	Point3 hit_point;
	Vec3   sur_normal;
	double ray_coeff;
	bool   front_faced;
	std::shared_ptr<Material> material;
	double u;
	double v;

	void set_against_ray(const Ray &ray, const Vec3 &out_normal);
};

class Hittable
{
  public:
	virtual bool hit(	const Ray &ray
						, Interval interval
						, Hit_record &record) const = 0;

	virtual AABB bounding_box() const = 0;

	virtual ~Hittable();
};

class Translate : public Hittable
{
  private:
	std::shared_ptr<Hittable> object;
	Vec3 offset;
	AABB bbox;

  public:
	Translate(std::shared_ptr<Hittable> _object, const Vec3 &_offset);

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override;

	AABB bounding_box() const override;
};

class Rotate_y : public Hittable
{
  private:
	std::shared_ptr<Hittable> object;
	double sin_theta;
	double cos_theta;
	AABB bbox;

  public:
	Rotate_y(std::shared_ptr<Hittable> _object, double angle);

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override;

	AABB bounding_box() const override;
};


#endif
