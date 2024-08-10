#include "hittables.h"

#include <vector>
#include <memory>

Hittables::Hittables() {}

Hittables::Hittables(std::shared_ptr<Hittable> object)
{
	add(object);
}

void Hittables::add(std::shared_ptr<Hittable> object)
{
	container.push_back(object);
	b_box = AABB(b_box, object->bounding_box());
}

void Hittables::clear()
{
	container.clear();
}

bool Hittables::hit(	const Ray &ray
			, Interval interval
			, Hit_record &record) const
{
	Hit_record temp_record = {};

	bool hit_anything = false;

	double closest_coeff = interval.max;

	for(const auto &object : container)
	{
		if(object->hit(ray, Interval(interval.min, closest_coeff), temp_record))
		{
			hit_anything 	= true;
			record 			= temp_record;
			closest_coeff 	= record.ray_coeff;
		}
	}

	return hit_anything;
}

AABB Hittables::bounding_box() const
{
	return b_box;
}
