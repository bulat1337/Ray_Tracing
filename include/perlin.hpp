#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <cmath>

#include <algorithm>
#include <memory>

#include "utils.hpp"
#include "vec3.hpp"

class Perlin
{
  public:
	Perlin()
	{
		size_t point_amount = static_cast<size_t>(point_count);

		rand_vec     = std::make_unique<Vec3[]>(point_amount);

		for(size_t id = 0 ; id < point_amount ; ++id)
		{
			rand_vec[id] = unit_vector(Vec3::random(-1, 1));
		}

		perm_x = perlin_gen_perm();
		perm_y = perlin_gen_perm();
		perm_z = perlin_gen_perm();
	}

	Perlin(const Perlin &other)				 = delete;
	Perlin &operator = (const Perlin &other) = delete;

	double noise(const Point3 &point) const
	{
		double floor_x = floor(point.x());
		double floor_y = floor(point.y());
		double floor_z = floor(point.z());

		double frac_portion_x = point.x() - floor_x;
		double frac_portion_y = point.y() - floor_y;
		double frac_portion_z = point.z() - floor_z;

		int i = static_cast<int>(floor_x);
		int j = static_cast<int>(floor_y);
		int k = static_cast<int>(floor_z);
		Vec3 c[2][2][2];

		for(int id_1 = 0 ; id_1 < 2 ; ++id_1)
		{
			for(int id_2 = 0 ; id_2 < 2 ; ++id_2)
			{
				for(int id_3 = 0 ; id_3 < 2 ; ++id_3)
				{
					const int mask = 255;

					int rand_id = 	perm_x[(i + id_1) & mask] ^
									perm_y[(j + id_2) & mask] ^
									perm_z[(k + id_3) & mask];

					c[id_1][id_2][id_3] = rand_vec[rand_id];
				}
			}
		}

		return perlin_interp(c, frac_portion_x, frac_portion_y, frac_portion_z);
	}

	double turbulence(const Point3 &point, int depth) const
	{
		double accum      = 0.0;
		double weight    = 1.0;
		Point3 tmp_point = point;

		for(int id = 0 ; id < depth ; ++id)
		{
			accum     += weight * noise(tmp_point);
			weight    /= 2;
			tmp_point *= 2;
		}

		return fabs(accum);
	}

  private:
	static const int          point_count;
	std::unique_ptr<int[]>    perm_x;
	std::unique_ptr<int[]>    perm_y;
	std::unique_ptr<int[]>    perm_z;
	std::unique_ptr<Vec3[]>   rand_vec;

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

	static double perlin_interp(	 const Vec3 c[2][2][2]
									, double frac_portion_x
									, double frac_portion_y
									, double frac_portion_z)
	{
		frac_portion_x = frac_portion_x * frac_portion_x * (3 - 2 * frac_portion_x);
		frac_portion_y = frac_portion_y * frac_portion_y * (3 - 2 * frac_portion_y);
		frac_portion_z = frac_portion_z * frac_portion_z * (3 - 2 * frac_portion_z);

		double accum = 0.0;

		for(int i = 0 ; i < 2 ; ++i)
		{
			for(int j = 0 ; j < 2 ; ++j)
			{
				for(int k = 0 ; k < 2 ; ++k)
				{
					Vec3 weight_v(	frac_portion_x - i
									, frac_portion_y - j
									, frac_portion_z - k);

					accum += 	(i * frac_portion_x + (1 - i) * (1 - frac_portion_x))
								* (j * frac_portion_y + (1 - j) * (1 - frac_portion_y))
								* (k * frac_portion_z + (1 - k) * (1 - frac_portion_z))
								* dot(c[i][j][k], weight_v);
				}
			}
		}

		return accum;
	}
};

const int Perlin::point_count = 256;


#endif // PERLIN_HPP
