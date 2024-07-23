#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <memory>

#include "color.hpp"
#include "vec3.hpp"

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



#endif
