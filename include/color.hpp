#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"
#include "interval.hpp"

const double color_coeff = 255.999;

using Color = Vec3;

inline double linear_to_gamma(double linera_component)
{
	if(linera_component > 0)
	{
		return std::sqrt(linera_component);
	}

	return 0;
}

std::ostream &print_color(std::ostream &out, const Color &color)
{
	Interval intensity(0.000, 0.999);

	double red 		= linear_to_gamma(color.x());
	double blue 	= linear_to_gamma(color.y());
	double green 	= linear_to_gamma(color.z());

	int red_byte 	= static_cast<int>(intensity.clamp(red)   * color_coeff);
	int green_byte 	= static_cast<int>(intensity.clamp(blue)  * color_coeff);
	int blue_byte 	= static_cast<int>(intensity.clamp(green) * color_coeff);

	out << red_byte << ' ' << green_byte << ' ' << blue_byte << "\n";

	return out;
}


#endif
