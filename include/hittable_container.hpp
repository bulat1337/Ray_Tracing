#ifndef HITTABLE_CONTAINER_HPP
#define HITTABLE_CONTAINER_HPP

#include <vector>
#include <memory>

#include "hittable.hpp"

class Hittable_container : public Hittable
{
	public:
		std::vector<std::shared_ptr<Hittable>> container;

		Hittable_container() = default;
		Hittable_container(std::shared_ptr<Hittable> object)
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
					, double min_coeff
					, double max_coeff
					, Hit_record &record) const override
		{
			Hit_record temp_record = {};

			bool hit_anything = false;

			double closest_coeff = max_coeff;

			for(const auto &object : container)
			{
				if(object->hit(ray, min_coeff, closest_coeff, temp_record))
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
