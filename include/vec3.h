#ifndef VEC_3_HPP
#define VEC_3_HPP

#include <cmath>
#include <iostream>

#include "utils.h"

class Vec3
{
  private:
	double coords[3];

  public:
	Vec3();

	Vec3(double x, double y, double z);

	const double &x() const;

	const double &y() const;

	const double &z() const;

	double operator [] (size_t id) const;

	double &operator [] (size_t id);

	Vec3 &operator +=(const Vec3 &other);

	Vec3 &operator *=(double scalar);

	Vec3 &operator /=(double scalar);

	Vec3 operator - () const;

	double sq_length() const;

	double length() const;

	static Vec3 random();

	static Vec3 random(double min, double max);

	bool near_zero() const;
};

Vec3 operator + (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator - (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator * (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator * (const Vec3 &lhs, double scalar);
Vec3 operator * (double scalar, const Vec3 &vector);
Vec3 operator / (const Vec3 &vector, double scalar);

std::ostream &operator << (std::ostream &out, const Vec3 &vector);

double dot(const Vec3 &lhs, const Vec3 &rhs);

Vec3 cross            (const Vec3& lhs, const Vec3& rhs);
Vec3 unit_vector      (const Vec3 &vector);
Vec3 rand_in_unit_sp  ();
Vec3 rand_unit_vec    ();
Vec3 rand_in_unit_disk();
Vec3 rand_on_hemisp   (const Vec3 &normal);
Vec3 reflect          (const Vec3 &ray_dir, const Vec3 &normal);
Vec3 refract          (const Vec3 &in_ray_dir, const Vec3 &normal, double index_ratio);

using Point3 = Vec3;



#endif
