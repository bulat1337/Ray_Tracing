#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

const double color_coeff = 255.999;

using Color = Vec3;

std::ostream &print_color(std::ostream &out, const Color &color)
{
	int red 	= static_cast<int>(color.x() * color_coeff);
	int green 	= static_cast<int>(color.y() * color_coeff);
	int blue 	= static_cast<int>(color.z() * color_coeff);

	out << red << ' ' << green << ' ' << blue << "\n";

	return out;
}


#endif
