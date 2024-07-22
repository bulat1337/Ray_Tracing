#ifndef VEC_3_HPP
#define VEC_3_HPP

#include <cmath>
#include <iostream>

#include "utils.hpp"

class Vec3
{
private:
	double coords[3];
public:
	Vec3(): coords{0, 0, 0} {}

	Vec3(double x, double y, double z)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
	}

	const double &x() const
	{
		return coords[0];
	}

	const double &y() const
	{
		return coords[1];
	}

	const double &z() const
	{
		return coords[2];
	}

	double operator [] (size_t id) const
	{
		return coords[id];
	}

	double &operator [] (size_t id)
	{
		return coords[id];
	}

	Vec3 &operator +=(const Vec3 &other)
	{
		coords[0] += other.coords[0];
		coords[1] += other.coords[1];
		coords[2] += other.coords[2];

		return *this;
	}

	Vec3 &operator *=(double scalar)
	{
		coords[0] *= scalar;
		coords[1] *= scalar;
		coords[2] *= scalar;

		return *this;
	}

	Vec3 &operator /=(double scalar)
	{
		return *this *= (1 / scalar);
	}

	Vec3 operator - () const
	{
		return Vec3(-coords[0], -coords[1], -coords[2]);
	}

	double sq_length() const
	{
		return 	coords[0] * coords[0] +
				coords[1] * coords[1] +
				coords[2] * coords[2];
	}

	double length() const
	{
		return std::sqrt(sq_length());
	}

	static Vec3 random()
	{
		return Vec3(	rand_double()
						, rand_double()
						, rand_double());
	}

	static Vec3 random(double min, double max)
	{
		return Vec3(	rand_double(min, max)
						, rand_double(min, max)
						, rand_double(min, max)	);
	}

	bool near_zero() const
	{
		double eps = 1e-8;

		return 	(std::fabs(coords[0]) < eps) &&
				(std::fabs(coords[1]) < eps) &&
				(std::fabs(coords[2]) < eps);
	}

};

inline Vec3 operator + (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(	lhs.x() + rhs.x(),
					lhs.y() + rhs.y(),
					lhs.z() + rhs.z()	);
}

inline Vec3 operator - (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(	lhs.x() - rhs.x(),
					lhs.y() - rhs.y(),
					lhs.z() - rhs.z()	);
}

inline Vec3 operator * (const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(	lhs.x() * rhs.x(),
					lhs.y() * rhs.y(),
					lhs.z() * rhs.z()	);
}

inline Vec3 operator * (const Vec3 &lhs, double scalar)
{
	return Vec3(	lhs.x() * scalar,
					lhs.y() * scalar,
					lhs.z() * scalar	);
}

inline Vec3 operator * (double scalar, const Vec3 &vector)
{
	return vector * scalar;
}

inline Vec3 operator / (const Vec3 &vector, double scalar)
{
	return vector * (1 / scalar);
}

inline std::ostream &operator << (std::ostream &out, const Vec3 &vector)
{
	out << vector.x() << ' ' << vector.y() << ' ' << vector.z();

	return out;
}

inline double dot(const Vec3 &lhs, const Vec3 &rhs)
{
	return 	lhs.x() * rhs.x() +
			lhs.y() * rhs.y() +
			lhs.z() * rhs.z();
}

inline Vec3 cross(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3(	lhs.y() * rhs.z() - lhs.z() * rhs.y(),
					lhs.z() * rhs.x() - lhs.x() * rhs.z(),
					lhs.x() * rhs.y() - lhs.y() * rhs.x()	);
}

inline Vec3 unit_vector(const Vec3 &vector)
{
	return vector / vector.length();
}

inline Vec3 rand_in_unit_sp()
{
	while(true)
	{
		Vec3 vec = Vec3::random(-1, 1);

		if(vec.sq_length() < 1)
		{
			return vec;
		}
	}
}

inline Vec3 rand_unit_vec()
{
	return unit_vector(rand_in_unit_sp());
}

inline Vec3 rand_in_unit_disk()
{
	while(true)
	{
		Vec3 vec = Vec3(rand_double(-1, 1), rand_double(-1, 1), 0);

		if(vec.sq_length() < 1)
		{
			return vec;
		}
	}
}

inline Vec3 rand_on_hemisp(const Vec3 &normal)
{
	Vec3 on_unit_sphere = rand_unit_vec();

	if(dot(on_unit_sphere, normal) > 0.0)
	{
		return on_unit_sphere;
	}
	else
	{
		return -on_unit_sphere;
	}

}

inline Vec3 reflect(const Vec3 &ray_dir, const Vec3 &normal)
{
	return ray_dir - 2.0 * dot(ray_dir, normal) * normal;
}

inline Vec3 refract(const Vec3 &in_ray_dir, const Vec3 &normal, double index_ratio)
{
	double cos_theta       = std::fmin(dot(-in_ray_dir, normal), 1.0);

	Vec3 out_ray_perp      = index_ratio * (in_ray_dir + cos_theta * normal);
	Vec3 out_ray_pharallel = -std::sqrt(std::fabs(1.0 - out_ray_perp.sq_length())) * normal;

	return out_ray_perp + out_ray_pharallel;
}

using Point3 = Vec3;



#endif
