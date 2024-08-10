#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

const double color_coeff = 255.999;

using Color = Vec3;

double        linear_to_gamma(double linera_component);
std::ostream &print_color    (std::ostream &out, const Color &color);


#endif
