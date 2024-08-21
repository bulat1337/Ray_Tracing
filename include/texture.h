#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cmath>

#include <memory>

#include "color.h"
#include "vec3.h"
#include "image_proc.h"
#include "perlin.h"

class Texture
{
  public:
	virtual ~Texture();

	virtual Color value(double u, double v, const Point3 &point) const = 0;
};

class Solid_color : public Texture
{
  public:
	Solid_color(const Color &_albedo);

	Solid_color(double red, double green, double blue);

	Color value(double /*u*/, double /*v*/, const Point3 &/*point*/) const override;

  private:
	Color albedo;
};

class Checker : public Texture
{
  private:
	double scale;
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;

  public:
	Checker(double _scale
			, std::shared_ptr<Texture> _even
			, std::shared_ptr<Texture> _odd);

	Checker(double _scale, const Color &_even, const Color &_odd);

	Color value(double u, double v, const Point3 &point) const override;
};

class Image_texture : public Texture
{
  public:
	Image_texture(const char *file_name);

	Color value(double u, double v, const Point3 &/*point*/) const override;

  private:
	External_img image;
};

class Noise : public Texture
{
  public:
	Noise();

	Noise(double _scale);

	Color value(double /*u*/, double /*v*/, const Point3 &point) const override;

  private:
	Perlin perlin;
	double scale = 1;
};


#endif
