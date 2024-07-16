#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class Sphere : public Hittable
{
private:
	Point3 center;
	double radius = 0.0;

public:
	Sphere(const Point3 &set_center, double set_radius):
		center(set_center),
		radius(fmax(set_radius, 0)) {}

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override
	{
		Vec3 sp_to_orig = center - ray.origin();

		double coeff_a = ray.direction().sq_length();
		double coeff_b = dot(ray.direction(), sp_to_orig);
		double coeff_c = sp_to_orig.sq_length() - radius * radius;

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


		return true;
	}
};

#endif
