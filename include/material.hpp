#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "ray.hpp"
#include "hittable.hpp"


class Material
{
  public:
	virtual bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const = 0;


	virtual ~Material() = default;
};

class Lambertian : public Material
{
  private:
	Color albedo;

  public:
	Lambertian(const Color &set_albedo):
		albedo(set_albedo) {}

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override
	{
		Vec3 scatter_dir = record.sur_normal + rand_unit_vec();

		if(scatter_dir.near_zero()) scatter_dir = record.sur_normal;

		scattered_ray = Ray(record.hit_point, scatter_dir);
		attenuation = albedo;

		return true;
	}
};

class Metal : public Material
{
  private:
	Color albedo;

  public:
	Metal(const Color &set_albedo):
		albedo(set_albedo) {}

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override
	{
		Vec3 scatter_dir = reflect(in_ray.direction(), record.sur_normal);

		scattered_ray = Ray(record.hit_point, scatter_dir);
		attenuation = albedo;

		return true;
	}
};




#endif
