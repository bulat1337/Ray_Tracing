#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.h"
#include "aabb.h"

class Sphere : public Hittable
{
  private:
	Point3	start_center;
	Vec3	path_dir;
	double	radius = 0.0;
	std::shared_ptr<Material> 	material;
	bool   	is_moving;
	AABB	b_box;

	Point3 current_center(double time) const;

	static void get_sphere_uv(	const Point3 &point
								, double &u
								, double &v);

  public:
	Sphere(	const Point3 &_start_center
			, double _radius
			, std::shared_ptr<Material> _material);

	Sphere(	const Point3 &_start_center
			, const Point3 &_end_center
			, double _radius
			, std::shared_ptr<Material> _material);

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override;

	AABB bounding_box() const override;
};

#endif
