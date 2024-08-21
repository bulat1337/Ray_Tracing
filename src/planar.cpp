#include "planar.h"

#include <cmath>

#include <memory>

Planar::Planar(	const Point3 &_plane_orig
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

void Planar::set_bound_box()
{
	AABB main_diag_bbox      = AABB(plane_orig + u, plane_orig + v);
	AABB secondary_diag_bbox = AABB(plane_orig, plane_orig + u + v);

	bbox = AABB(main_diag_bbox, secondary_diag_bbox);
}

AABB Planar::bounding_box() const { return bbox; }

bool Planar::hit(	const Ray &ray
					, Interval interval
					, Hit_record &record) const
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


bool Quad::is_inside(double coeff_u, double coeff_v, Hit_record &record) const
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


Disk::Disk(	const Point3 &_plane_orig
		, const Vec3 &_u
		, const Vec3 &_v
		, std::shared_ptr<Material> _material
		, double _radius):
	Planar(_plane_orig, _u, _v, _material), radius(_radius) {}

bool Disk::is_inside(double coeff_u, double coeff_v, Hit_record &record) const
{
	if(!(std::sqrt(coeff_u * coeff_u + coeff_v * coeff_v) < radius))
	{
		return false;
	}

	record.u = coeff_u;
	record.v = coeff_v;

	return true;
}


bool Triangle::is_inside(double coeff_u, double coeff_v, Hit_record &record) const
{
	if(!(coeff_u > 0 && coeff_v > 0 && coeff_u + coeff_v < 1))
	{
		return false;
	}

	record.u = coeff_u;
	record.v = coeff_v;

	return true;
}

std::shared_ptr<Hittables> create_box(	const Point3 &a
										, const Point3 &b
										, std::shared_ptr<Material> material)
{
	std::shared_ptr<Hittables> sides = std::make_shared<Hittables>();

	Point3 min(	fmin(a.x(), b.x())
				, fmin(a.y(), b.y())
				, fmin(a.z(), b.z()));

	Point3 max(	fmax(a.x(), b.x())
				, fmax(a.y(), b.y())
				, fmax(a.z(), b.z()));

	Vec3 axis_x(max.x() - min.x(), 0, 0);
	Vec3 axis_y(0, max.y() - min.y(), 0);
	Vec3 axis_z(0, 0, max.z() - min.z());

	sides->add(std::make_shared<Quad>(	Point3(min.x()
										, min.y()
										, max.z())
										, axis_x
										, axis_y
										, material));  // front

	sides->add(std::make_shared<Quad>(	Point3(max.x()
										, min.y()
										, max.z())
										, -axis_z
										, axis_y
										, material)); // right

	sides->add(std::make_shared<Quad>(	Point3(max.x()
										, min.y()
										, min.z())
										, -axis_x
										, axis_y
										, material)); // back

	sides->add(std::make_shared<Quad>(	Point3(min.x()
										, min.y()
										, min.z())
										, axis_z
										, axis_y
										, material));  // left

	sides->add(std::make_shared<Quad>(	Point3(min.x()
										, max.y()
										, max.z())
										, axis_x
										, -axis_z
										, material)); // top

	sides->add(std::make_shared<Quad>(	Point3(min.x()
										, min.y()
										, min.z())
										, axis_x
										, axis_z
										, material));  // bottom

	return sides;
}
