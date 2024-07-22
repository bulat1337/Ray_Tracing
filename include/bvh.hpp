#ifndef BVH_HPP
#define BVH_HPP

#include <memory>
#include <algorithm>

#include "utils.hpp"
#include "hittables.hpp"
#include "aabb.hpp"


class BVH_node : public Hittable
{
  private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB bbox;

	static bool box_comp(	std::shared_ptr<Hittable> left
							, std::shared_ptr<Hittable> right
							, size_t axis_id)
	{
		Interval left_interval  = left->bounding_box().axis_interval(axis_id);
		Interval right_interval = right->bounding_box().axis_interval(axis_id);

		return left_interval.min < right_interval.min;
	}

	static bool box_x_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right)
	{
		return box_comp(left, right, 0);
	}

	static bool box_y_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right)
	{
		return box_comp(left, right, 1);
	}

	static bool box_z_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right)
	{
		return box_comp(left, right, 2);
	}

  public:
	BVH_node(std::vector<std::shared_ptr<Hittable>> objects, size_t start, size_t end)
	{
		bbox = AABB::empty;

		for(size_t id = start ; id < end ; ++id)
		{
			bbox = AABB(bbox, objects[id]->bounding_box());
		}

		int axis_id = bbox.longest_axis();

		bool (*comparator) (std::shared_ptr<Hittable> left, std::shared_ptr<Hittable> right)
			= nullptr;

		switch(axis_id)
		{
			case 0:
			{
				comparator = box_x_comp;
				break;
			}
			case 1:
			{
				comparator = box_y_comp;
				break;
			}
			case 2:
			{
				comparator = box_z_comp;
				break;
			}
		}

		size_t obj_span = end - start;

		switch(obj_span)
		{
			case 1:
			{
				left  = objects[start];
				right = objects[start];
				break;
			}
			case 2:
			{
				left  = objects[start];
				right = objects[start + 1];
				break;
			}
			default:
			{
				using diff_type = std::vector<std::shared_ptr<Hittable>>::difference_type;

				std::sort(	objects.begin()   + static_cast<diff_type>(start)
							, objects.begin() + static_cast<diff_type>(end)
							, comparator);

				auto mid = start + obj_span / 2;

				left  = std::make_shared<BVH_node>(objects, start, mid);
				right = std::make_shared<BVH_node>(objects, mid,   end);
			}
		}
	}

	BVH_node(Hittables hittables):
		BVH_node(hittables.container, 0, hittables.container.size()) {}

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override
	{
		if(!bbox.hit(ray, interval)) return false;

		bool hit_left  = left->hit(ray, interval, record);

		Interval after_itnerval(interval.min, hit_left ? record.ray_coeff : interval.max);

		bool hit_right = right->hit(ray, after_itnerval, record);

		return hit_left || hit_right;
	}

	AABB bounding_box() const override
	{
		return bbox;
	}

};

#endif
