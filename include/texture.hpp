#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>

#include "color.hpp"
#include "vec3.hpp"
#include "stb_image.hpp"
#include "perlin.hpp"

class Texture
{
  public:
	virtual ~Texture() = default;

	virtual Color value(double u, double v, const Point3 &point) const = 0;
};

class Solid_color : public Texture
{
  public:
	Solid_color(const Color &set_albedo):
		albedo(set_albedo) {}

	Solid_color(double red, double green, double blue):
		Solid_color(Color(red, green, blue)) {}

	Color value(double /*u*/, double /*v*/, const Point3 &/*point*/) const override
	{
		return albedo;
	}

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
	Checker(double set_scale
			, std::shared_ptr<Texture> set_even
			, std::shared_ptr<Texture> set_odd):
		scale(set_scale)
		, even(set_even)
		, odd(set_odd) {}

	Checker(double set_scale, const Color &set_even, const Color &set_odd):
		scale(set_scale)
		,even(std::make_shared<Solid_color>(set_even))
		,odd(std::make_shared<Solid_color>(set_odd)) {}

	Color value(double u, double v, const Point3 &point) const override
	{
		int x_floored = static_cast<int>(std::floor(point.x() / scale));
		int y_floored = static_cast<int>(std::floor(point.y() / scale));
		int z_floored = static_cast<int>(std::floor(point.z() / scale));

		bool is_even = (x_floored + y_floored + z_floored) % 2 == 0;

		return is_even ? even->value(u, v, point) : odd->value(u, v, point);
	}
};

class Image_texture : public Texture
{
  public:
	Image_texture(const char *file_name):
		image(file_name) {}

	Color value(double u, double v, const Point3 &point) const override
	{
		if(image.height() <= 0) return Color(0, 1, 1);

		u = Interval(0, 1).clamp(u);

		v = 1.0 - Interval(0, 1).clamp(v);

		int i = static_cast<int>(u * image.width());
		int j = static_cast<int>(v * image.height());

		const unsigned char* pixel = image.pixel_data(i, j);

		double scale = 1.0 / 255.0;

		return Color(	pixel[0] * scale
						, pixel[1] * scale
						, pixel[2] * scale);
	}

  private:
	External_img image;


};

class Noise : public Texture
{
  public:
	Noise() = default;

	Color value(double /*u*/, double /*v*/, const Point3 &point) const
	{
		return Color(1, 1, 1) * perlin.noise(point);
	}

  private:
	Perlin perlin;
};


#endif
