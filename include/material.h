#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "texture.h"


class Material
{
  public:
	virtual bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const = 0;

	virtual Color emitted(double /*u*/, double /*v*/, const Point3 &/*point*/) const;

	virtual ~Material();
};

class Lambertian : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Lambertian(const Color &albedo);

	Lambertian(std::shared_ptr<Texture> _texture);

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override;
};

class Metal : public Material
{
  private:
	Color albedo;
	double fuzz;

  public:
	Metal(const Color &_albedo, double _fuzz);

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override;
};

class Dielectric : public Material
{
  private:
	double refraction_id;

	static double reflectance(double cosine, double refraction_id);

  public:
	Dielectric(double _refraction_id);

	virtual bool scattered(	const Ray &in_ray
							, const Hit_record &record
							, Color &attenuation
							, Ray &scattered_ray) const override;
};

class Diffuse_light : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Diffuse_light(std::shared_ptr<Texture> _texture);

	Diffuse_light(const Color& emit);

	Color emitted(double u, double v, const Point3 &point) const override;

	bool scattered(	const Ray &/*in_ray*/
					, const Hit_record &/*record*/
					, Color &/*attenuation*/
					, Ray &/*scattered_ray*/) const override;
};

class Isotropic : public Material
{
  private:
	std::shared_ptr<Texture> texture;

  public:
	Isotropic(const Color &albedo);

	Isotropic(std::shared_ptr<Texture> _texture);

	bool scattered(	const Ray &in_ray
					, const Hit_record &record
					, Color &attenuation
					, Ray &scattered_ray) const override;
};


#endif
