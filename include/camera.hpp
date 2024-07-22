#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <fstream>
#include <chrono>

#include "color.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "hittables.hpp"
#include "material.hpp"

class Camera
{
  public:
	double aspect_ratio		= 1;
	size_t image_width 		= 400;
	size_t sampling			= 1;
	size_t diffusion_depth	= 10;
	double vertical_FOV     = 90;

	Point3 lookfrom         = Point3(0, 0, 0);
	Point3 lookat           = Point3(0, 0, -1);
	Vec3   view_up          = Vec3(0, 1, 0);

	double defocus_angle = 0;
	double focus_dist    = 10;

	Camera() = default;

	void render(const Hittables world)
	{
		open_file("image.ppm");

		initialize();

		image_file << "P3\n";
		image_file << image_width << ' ' << image_height << "\n";
		image_file << "255\n";

		std::clog << "Render start.\n" << std::flush;

		for(size_t row = 0 ; row < image_height ; ++row)
		{
			Time_guard time_guard;
			std::clog << image_height - row << " rows remaining.\n" << std::flush;

			for(size_t col = 0 ; col < image_width ; ++col)
			{
				Color pixel_color(0, 0, 0);

				for(size_t id = 0 ; id < sampling ; ++id)
				{
					Ray ray = get_sample_ray(col, row);

					pixel_color += ray_color(ray, diffusion_depth, world);
				}

				print_color(image_file, pixel_color * sampling_scale);
			}
		}

		std::clog << "Render end.\n" << std::flush;
	}


  private:
	size_t image_height = 0;
	Point3 camera_center;
	Point3 pixel_0_0;

	Vec3 delta_u;
	Vec3 delta_v;

	std::ofstream image_file;
	double sampling_scale = 1;

	Vec3 u_axis;
	Vec3 v_axis;
	Vec3 w_axis;

	Vec3 defocus_disk_u;
	Vec3 defocus_disk_v;

	void initialize()
	{
		sampling_scale = 1.0 / sampling;
		image_height = static_cast<size_t>(image_width / aspect_ratio);


		if(image_height < 1)
		{
			image_height = 1;
		}

		camera_center = lookfrom;

		double theta = degrees_to_radians(vertical_FOV);
		double h     = std::tan(theta / 2);

		double viewport_height = 2 * h * focus_dist;
		double viewport_width  = viewport_height * (double(image_width) / image_height);

		w_axis = unit_vector(lookfrom - lookat);
		u_axis = unit_vector(cross(view_up, w_axis));
		v_axis = cross(w_axis, u_axis);

		Vec3 viewport_u = viewport_width * u_axis;
		Vec3 viewport_v = viewport_height * (-v_axis);

		delta_u = viewport_u / image_width;
		delta_v = viewport_v / image_height;

		Point3 viewport_upper_left =
			camera_center - (focus_dist * w_axis) - viewport_u / 2 - viewport_v / 2;
		pixel_0_0 = viewport_upper_left + 0.5 * (delta_u + delta_v);

		double defocus_radius =
			focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
		defocus_disk_u = u_axis * defocus_radius;
		defocus_disk_v = v_axis * defocus_radius;
	}

	Color ray_color(const Ray &ray, size_t depth, const Hittables &world)
	{
		if(depth <= 0)
		{
			return Color(0, 0, 0);
		}

		Hit_record record;

		if(world.hit(ray, Interval(0.001, infinity), record))
		{
			Color attenuation;
			Ray scattered_ray;

			if(record.material->scattered(ray, record, attenuation, scattered_ray))
			{
				return attenuation * ray_color(scattered_ray, depth - 1, world);
			}

			return Color(0, 0, 0);
		}


		Vec3 unit_dir = unit_vector(ray.direction());

		double coeff = 0.5 * (unit_dir.y() + 1);
		Color start_color(1, 1, 1);
		Color end_color(0.5, 0.7, 1.0);

		return (1 - coeff) * start_color + coeff * end_color;
	}


	void open_file(const char *file_name)
	{
		image_file = std::ofstream(file_name);

		if(!image_file.is_open())
		{
			throw std::ofstream::failure("Unable to open image_file\n");
		}
	}

	Ray get_sample_ray(size_t col, size_t row) const
	{
		Vec3 offset = sample_square();

		Point3 sample_pixel = pixel_0_0 +
						(offset.x() + col) * delta_u +
						(offset.y() + row) * delta_v;

		Point3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();

		double ray_time = rand_double();

		return Ray(ray_origin, sample_pixel - ray_origin, ray_time);
	}

	Vec3 sample_square() const
	{
		return Vec3(rand_double() - 0.5, rand_double() - 0.5, 0);
	}

	Point3 defocus_disk_sample() const
	{
		Vec3 point = rand_in_unit_disk();

		return camera_center + (point[0] * defocus_disk_u) + (point[1] * defocus_disk_v);
	}
};

#endif
