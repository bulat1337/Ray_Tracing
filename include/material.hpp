#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "texture.hpp"


class Material
{
  public:
	virtual bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const = 0;

	virtual Color emitted(double /*u*/, double /*v*/, const Point3 &/*point*/) const
	{
		return Color(0, 0, 0);
	}


	virtual ~Material() = default;
};

class Lambertian : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Lambertian(const Color &albedo):
		texture(std::make_shared<Solid_color>(albedo)) {}

	Lambertian(std::shared_ptr<Texture> set_texture):
		texture(set_texture) {}

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override
	{
		Vec3 scatter_dir = record.sur_normal + rand_unit_vec();

		if(scatter_dir.near_zero()) scatter_dir = record.sur_normal;

		scattered_ray = Ray(record.hit_point, scatter_dir, in_ray.get_time());
		attenuation   = texture->value(record.u, record.v, record.hit_point);

		return true;
	}
};

class Metal : public Material
{
  private:
	Color albedo;
	double fuzz;

  public:
	Metal(const Color &set_albedo, double set_fuzz):
		albedo(set_albedo)
		, fuzz(set_fuzz < 1 ? set_fuzz : 1) {}

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override
	{
		Vec3 scatter_dir = reflect(in_ray.direction(), record.sur_normal);

		scatter_dir = unit_vector(scatter_dir) + fuzz * rand_unit_vec();

		scattered_ray = Ray(record.hit_point, scatter_dir, in_ray.get_time());
		attenuation   = albedo;

		return dot(scatter_dir, record.sur_normal) > 0;
	}
};

class Dielectric : public Material
{
  private:
	double refraction_id;

	static double reflectance(double cosine, double refraction_id)
	{
		double r0 = (1 - refraction_id) / (1 + refraction_id);

		r0 *= r0;

		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

  public:
	Dielectric(double set_refraction_id):
		refraction_id(set_refraction_id) {}

	virtual bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const override
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
};

class Diffuse_light : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Diffuse_light(std::shared_ptr<Texture> _texture):
		texture(_texture) {}

	Diffuse_light(const Color& emit):
		texture(std::make_shared<Solid_color>(emit)) {}

	Color emitted(double u, double v, const Point3 &point) const override
	{
		return texture->value(u, v, point);
	}

	bool scattered(	const Ray &/*in_ray*/
							, const Hit_record &/*record*/
							, Color &/*attenuation*/
							, Ray &/*scattered_ray*/) const override
	{
		return false;
	}
};

class Isotropic : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Isotropic(const Color &albedo):
		texture(std::make_shared<Solid_color> (albedo)) {}

	Isotropic(std::shared_ptr<Texture> _texture):
		texture(_texture) {}

	bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const override
	{
		scattered_ray = Ray(record.hit_point, rand_unit_vec(), in_ray.get_time());
		attenuation = texture->value(record.u, record.v, record.hit_point);

		return true;
	}
};




#endif
