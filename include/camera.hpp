#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <fstream>

#include "color.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "hittables.hpp"

class Camera
{
  public:
	double aspect_ratio	= 1;
	size_t image_width  		= 100;

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
			std::clog << "Loading row: " << row << '\n' << std::flush;

			for(size_t col = 0 ; col < image_width ; ++col)
			{
				Point3 pixel_center = pixel_0_0 + row * (delta_v) + col * (delta_u);

				Vec3 ray_dir = pixel_center - camera_center;

				Ray ray(camera_center, ray_dir);

				auto pixel_color = ray_color(ray, world);
				print_color(image_file, pixel_color);
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

	void initialize()
	{
		image_height = static_cast<size_t>(image_width / aspect_ratio);

		if(image_height < 1)
		{
			image_height = 1;
		}

		camera_center = Point3(0, 0, 0);

		double focal_length = 1.0;

		double viewport_height = 2.0;
		double viewport_width  = viewport_height * (double(image_width) / image_height);

		Vec3 viewport_u(viewport_width, 0, 0);
		Vec3 viewport_v(0, -viewport_height, 0);

		delta_u = viewport_u / image_width;
		delta_v = viewport_v / image_height;

		Point3 viewport_upper_left =
			camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

		pixel_0_0 = viewport_upper_left + 0.5 * (delta_u + delta_v);

	}

	Color ray_color(const Ray &ray, const Hittables &world)
	{
		Hit_record hit_record;

		if(world.hit(ray, Interval(0, infinity), hit_record))
		{
			return 0.5 * (hit_record.sur_normal + Color(1, 1, 1));
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

};

#endif
