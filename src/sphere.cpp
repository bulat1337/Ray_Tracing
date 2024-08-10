#include "sphere.h"

#include "hittable.h"
#include "aabb.h"

Point3 Sphere::current_center(double time) const
{
	return start_center + path_dir * time;
}

void Sphere::get_sphere_uv(	const Point3 &point
							, double &u
							, double &v)
{
	auto theta = acos(-point.y());
	auto phi   = atan2(-point.z(), point.x()) + pi;

	u = phi / (2 * pi);
	v = theta / pi;
}

Sphere::Sphere(	const Point3 &_start_center
		, double _radius
		, std::shared_ptr<Material> _material):
	start_center(_start_center)
	, radius(fmax(_radius, 0))
	, material(_material)
	, is_moving(false)
{
	Vec3 r_vec(radius, radius, radius);
	b_box = AABB(start_center - r_vec, start_center + r_vec);
}

Sphere::Sphere(	const Point3 &_start_center
		, const Point3 &_end_center
		, double _radius
		, std::shared_ptr<Material> _material):
	start_center(_start_center)
	, radius(fmax(_radius, 0))
	, material(_material)
	, is_moving(true)
{
	Vec3 r_vec(radius, radius, radius);

	AABB start_b_box(start_center - r_vec, start_center   + r_vec);
	AABB end_b_box(_end_center - r_vec, _end_center + r_vec);

	b_box    = AABB(start_b_box, end_b_box);
	path_dir = _end_center - start_center;
}

bool Sphere::hit(	const Ray &ray
			, Interval interval
			, Hit_record &record) const
{
	Point3 sphere_center  = is_moving ? current_center(ray.get_time()) : start_center;
	Vec3   orig_to_spehre = sphere_center - ray.origin();

	double coeff_a = ray.direction().sq_length();
	double coeff_b = dot(ray.direction(), orig_to_spehre);
	double coeff_c = orig_to_spehre.sq_length() - radius * radius;

	double discriminant = coeff_b * coeff_b - coeff_a * coeff_c;

	if(cmp_double(discriminant, 0) < 0)
	{
		return false;
	}

	double sq_disc = std::sqrt(discriminant);
	double root    = (coeff_b - sq_disc) / coeff_a;

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

	record.material   = material;

	return true;
}

AABB Sphere::bounding_box() const
{
	return b_box;
}
