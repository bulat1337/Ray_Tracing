#include "texture.h"

#include <cmath>

#include <memory>

Texture::~Texture() {}

Solid_color::Solid_color(const Color &set_albedo):
	albedo(set_albedo) {}

Solid_color::Solid_color(double red, double green, double blue):
	Solid_color(Color(red, green, blue)) {}

Color Solid_color::value(double /*u*/, double /*v*/, const Point3 &/*point*/) const
{
	return albedo;
}

Checker::Checker(double set_scale
		, std::shared_ptr<Texture> set_even
		, std::shared_ptr<Texture> set_odd):
	scale(set_scale)
	, even(set_even)
	, odd(set_odd) {}

Checker::Checker(double set_scale, const Color &set_even, const Color &set_odd):
	scale(set_scale)
	,even(std::make_shared<Solid_color>(set_even))
	,odd(std::make_shared<Solid_color>(set_odd)) {}

Color Checker::value(double u, double v, const Point3 &point) const
{
	int x_floored = static_cast<int>(std::floor(point.x() / scale));
	int y_floored = static_cast<int>(std::floor(point.y() / scale));
	int z_floored = static_cast<int>(std::floor(point.z() / scale));

	bool is_even = (x_floored + y_floored + z_floored) % 2 == 0;

	return is_even ? even->value(u, v, point) : odd->value(u, v, point);
}


Image_texture::Image_texture(const char *file_name):
	image(file_name) {}

Color Image_texture::value(double u, double v, const Point3 &/*point*/) const
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


Noise::Noise() {}

Noise::Noise(double set_scale):
	scale(set_scale) {}

Color Noise::value(double /*u*/, double /*v*/, const Point3 &point) const
{
	return 	Color(0.5, 0.5, 0.5)
			* (	1.0 + sin(	scale * point.z()
							+ 10 * perlin.turbulence(point, 7))); // 7 -- magic number
}
