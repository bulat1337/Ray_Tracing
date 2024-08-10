#ifndef BVH_H
#define BVH_H

#include <memory>
#include <vector>

#include "utils.h"
#include "hittables.h"
#include "aabb.h"

class BVH_node : public Hittable
{
  public:
	BVH_node(std::vector<std::shared_ptr<Hittable>> objects, size_t start, size_t end);

	BVH_node(Hittables hittables);

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override;

	AABB bounding_box() const override;

  private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB bbox;

	static bool box_comp(	std::shared_ptr<Hittable> left
							, std::shared_ptr<Hittable> right
							, size_t axis_id);

	static bool box_x_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right);

	static bool box_y_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right);

	static bool box_z_comp(	const std::shared_ptr<Hittable> left
							, const std::shared_ptr<Hittable> right);
};

#endif
