#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "aabb.hpp"

class Sphere : public Hittable
{
private:
	Point3 center_1;
	Vec3   path_dir;
	double radius = 0.0;
	std::shared_ptr<Material> material;
	bool   is_moving;
	AABB b_box;

	Point3 current_center(double time) const
	{
		return center_1 + path_dir * time;
	}

	static void get_sphere_uv(	const Point3 &point
								, double &u
								, double &v)
	{
		auto theta = acos(-point.y());
		auto phi   = atan2(-point.z(), point.x()) + pi;

		u = phi / (2 * pi);
		v = theta / pi;
	}

public:
	Sphere(	const Point3 &set_center_1
			, double set_radius
			, std::shared_ptr<Material> set_material):
		center_1(set_center_1)
		, radius(fmax(set_radius, 0))
		, material(set_material)
		, is_moving(false)
	{
		Vec3 r_vec(radius, radius, radius);
		b_box = AABB(center_1 - r_vec, center_1 + r_vec);
	}

	Sphere(	const Point3 &set_center_1
			, const Point3 &set_center_2
			, double set_radius
			, std::shared_ptr<Material> set_material):
		center_1(set_center_1)
		, radius(fmax(set_radius, 0))
		, material(set_material)
		, is_moving(true)
	{
		Vec3 r_vec(radius, radius, radius);

		AABB b_box_1(center_1 - r_vec, center_1 + r_vec);
		AABB b_box_2(set_center_2 - r_vec, set_center_2 + r_vec);

		b_box = AABB(b_box_1, b_box_2);

		path_dir = set_center_2 - center_1;
	}

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override
	{
		Point3 sphere_center = is_moving ? current_center(ray.get_time()) : center_1;
		Vec3 orig_to_spehre = sphere_center - ray.origin();

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

		Vec3 out_normal   = (record.hit_point - sphere_center) / radius;
		record.set_against_ray(ray, out_normal);

		get_sphere_uv(out_normal, record.u, record.v);

		record.material = material;


		return true;
	}

	AABB bounding_box() const override
	{
		return b_box;
	}
};

#endif
