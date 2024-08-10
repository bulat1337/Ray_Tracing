#include "material.h"

Material::~Material() {}

Color Material::emitted(double /*u*/, double /*v*/, const Point3 &/*point*/) const
{
	return Color(0, 0, 0);
}


Lambertian::Lambertian(const Color &albedo):
	texture(std::make_shared<Solid_color>(albedo)) {}

Lambertian::Lambertian(std::shared_ptr<Texture> set_texture):
	texture(set_texture) {}

bool Lambertian::scattered(	const Ray &in_ray
				, const Hit_record &record
				, Color &attenuation
				, Ray &scattered_ray) const
{
	Vec3 scatter_dir = record.sur_normal + rand_unit_vec();

	if(scatter_dir.near_zero()) scatter_dir = record.sur_normal;

	scattered_ray = Ray(record.hit_point, scatter_dir, in_ray.get_time());
	attenuation   = texture->value(record.u, record.v, record.hit_point);

	return true;
}


Metal::Metal(const Color &set_albedo, double set_fuzz):
	albedo(set_albedo)
	, fuzz(set_fuzz < 1 ? set_fuzz : 1) {}

bool Metal::scattered(	const Ray &in_ray
				, const Hit_record &record
				, Color &attenuation
				, Ray &scattered_ray) const
{
	Vec3 scatter_dir = reflect(in_ray.direction(), record.sur_normal);

	scatter_dir = unit_vector(scatter_dir) + fuzz * rand_unit_vec();

	scattered_ray = Ray(record.hit_point, scatter_dir, in_ray.get_time());
	attenuation   = albedo;

	return dot(scatter_dir, record.sur_normal) > 0;
}


double Dielectric::reflectance(double cosine, double refraction_id)
{
	double r0 = (1 - refraction_id) / (1 + refraction_id);

	r0 *= r0;

	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Dielectric::Dielectric(double set_refraction_id):
	refraction_id(set_refraction_id) {}

bool Dielectric::scattered(	const Ray &in_ray
						, const Hit_record &record
						, Color &attenuation
						, Ray &scattered_ray) const
{
	attenuation = Color(1.0, 1.0, 1.0);

	double real_id   = record.front_faced ? (1.0 / refraction_id) : refraction_id;

	Vec3 unit_dir    = unit_vector(in_ray.direction());

	double cos_theta = std::fmin(dot(-unit_dir, record.sur_normal), 1.0);
	double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

	Vec3 out_ray_dir;
	bool cannot_refract     = sin_theta * real_id > 1.0;
	bool reflectance_factor = reflectance(cos_theta, real_id) > rand_double();

	if(cannot_refract || reflectance_factor)
	{
		out_ray_dir = reflect(unit_dir, record.sur_normal);
	}
	else
	{
		out_ray_dir = refract(unit_dir, record.sur_normal, real_id);
	}

	scattered_ray = Ray(record.hit_point, out_ray_dir, in_ray.get_time());

	return true;
}


Diffuse_light::Diffuse_light(std::shared_ptr<Texture> _texture):
	texture(_texture) {}

Diffuse_light::Diffuse_light(const Color& emit):
	texture(std::make_shared<Solid_color>(emit)) {}

Color Diffuse_light::emitted(double u, double v, const Point3 &point) const
{
	return texture->value(u, v, point);
}

bool Diffuse_light::scattered(	const Ray &/*in_ray*/
						, const Hit_record &/*record*/
						, Color &/*attenuation*/
						, Ray &/*scattered_ray*/) const
{
	return false;
}


Isotropic::Isotropic(const Color &albedo):
	texture(std::make_shared<Solid_color> (albedo)) {}

Isotropic::Isotropic(std::shared_ptr<Texture> _texture):
	texture(_texture) {}

bool Isotropic::scattered(	const Ray &in_ray
						, const Hit_record &record
						, Color &attenuation
						, Ray &scattered_ray) const
{
	scattered_ray = Ray(record.hit_point, rand_unit_vec(), in_ray.get_time());
	attenuation = texture->value(record.u, record.v, record.hit_point);

	return true;
}
