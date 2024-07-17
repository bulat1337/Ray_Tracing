#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class Sphere : public Hittable
{
private:
	Point3 center;
	double radius = 0.0;
	std::shared_ptr<Material> material;

public:
	Sphere(	const Point3 &set_center
			, double set_radius
			, std::shared_ptr<Material> set_material):
		center(set_center)
		, radius(fmax(set_radius, 0))
		, material(set_material) {}

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override
	{
		Vec3 orig_to_spehre = center - ray.origin();

		double coeff_a = ray.direction().sq_length();
		double coeff_b = dot(ray.direction(), orig_to_spehre);
		double coeff_c = orig_to_spehre.sq_length() - radius * radius;

		double discriminant = coeff_b * coeff_b - coeff_a * coeff_c;

		if(cmp_double(discriminant, 0) < 0)
		{
			return false;
		}

		double sq_disc = std::sqrt(discriminant);
		double root = ( coeff_b - sq_disc ) / coeff_a;

		if(!interval.surrounds(root))
		{
			root = ( coeff_b + sq_disc ) / coeff_a;

			if(!interval.surrounds(root))
			{
				return false;
			}
		}

		record.ray_coeff  = root;
		record.hit_point  = ray.at(root);

		Vec3 out_normal   = (record.hit_point - center) / radius;
		record.set_against_ray(ray, out_normal);
		record.material = material;


		return true;
	}
};

#endif
