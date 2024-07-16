#ifndef HITTABLES_HPP
#define HITTABLES_HPP

#include <vector>
#include <memory>

#include "hittable.hpp"

class Hittables : public Hittable
{
public:
	std::vector<std::shared_ptr<Hittable>> container;

	Hittables() = default;
	Hittables(std::shared_ptr<Hittable> object)
	{
		add(object);
	}

	void add(std::shared_ptr<Hittable> object)
	{
		container.push_back(object);
	}

	void clear()
	{
		container.clear();
	}

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override
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
};

#endif
