#ifndef HITTABLES_HPP
#define HITTABLES_HPP

#include <vector>
#include <memory>

#include "hittable.h"

class Hittables : public Hittable
{
  private:
	AABB b_box;

  public:
	std::vector<std::shared_ptr<Hittable>> container;

	Hittables();

	Hittables(std::shared_ptr<Hittable> object);

	void add(std::shared_ptr<Hittable> object);

	void clear();

	bool hit(	const Ray &ray
				, Interval interval
				, Hit_record &record) const override;

	AABB bounding_box() const override;
};

#endif
