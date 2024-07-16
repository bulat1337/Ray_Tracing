#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"
#include "interval.hpp"

const double color_coeff = 255.999;

using Color = Vec3;

std::ostream &print_color(std::ostream &out, const Color &color)
{
	Interval intensity(0.000, 0.999);

	int red 	= static_cast<int>(intensity.clamp(color.x()) * color_coeff);
	int green 	= static_cast<int>(intensity.clamp(color.y()) * color_coeff);
	int blue 	= static_cast<int>(intensity.clamp(color.z()) * color_coeff);

	out << red << ' ' << green << ' ' << blue << "\n";

	return out;
}


#endif
