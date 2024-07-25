#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <memory>
#include <algorithm>

#include "utils.hpp"

class Perlin
{
  public:
	Perlin()
	{
		rand_doubles = std::make_unique<double[]>(point_count);

		for(size_t id = 0 ; id < point_count ; ++id)
		{
			rand_doubles[id] = rand_double();
		}

		perm_x = perlin_gen_perm();
		perm_y = perlin_gen_perm();
		perm_z = perlin_gen_perm();
	}

	Perlin(const Perlin &other)				 = delete;
	Perlin &operator = (const Perlin &other) = delete;

	double noise(const Point3 &point) const
	{
		const int mask = 255;
		int i = static_cast<int>(4 * point.x()) & mask;
		int j = static_cast<int>(4 * point.y()) & mask;
		int k = static_cast<int>(4 * point.z()) & mask;

		return rand_doubles[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
	}

  private:
	static const size_t point_count;
	std::unique_ptr<double[]> rand_doubles;
	std::unique_ptr<int[]> perm_x;
	std::unique_ptr<int[]> perm_y;
	std::unique_ptr<int[]> perm_z;

	static std::unique_ptr<int[]> perlin_gen_perm()
	{
		std::unique_ptr<int[]> perm = std::make_unique<int[]>(point_count);

		for(int id = 0 ; id < point_count ; ++id)
		{
			perm[id] = id;
		}

		permute(perm.get());

		return perm;
	}

	static void permute(int *perm)
	{
		for(int id = point_count - 1 ; id > 0 ; --id)
		{
			int rand_id = rand_int(0, id);

			std::swap(perm[id], perm[rand_id]);
		}
	}
};

const size_t Perlin::point_count = 256;


#endif // PERLIN_HPP
