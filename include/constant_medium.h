#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include <cmath>

#include <memory>

#include "utils.h"
#include "hittable.h"
#include "material.h"

class Constant_medium : public Hittable
{
  private:
	std::shared_ptr<Hittable> 	boundary;
	double 						density;
	std::shared_ptr<Material> 	phase_func;

  public:
	Constant_medium	(	std::shared_ptr<Hittable> _boundary
						, double _density
						, std::shared_ptr<Texture> texture);

	Constant_medium	(	std::shared_ptr<Hittable> _boundary
						, double _density
						, const Color &albedo);

	bool hit		(	const Ray &ray
						, Interval interval
						, Hit_record &record) const override;

	AABB bounding_box() const override;
};


#endif
