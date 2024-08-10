#include "camera.h"

#include <iostream>
#include <fstream>
#include <chrono>

Camera::Camera() {}

void Camera::render(const Hittables world)
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


void Camera::initialize()
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

Color Camera::ray_color(const Ray &ray, size_t depth, const Hittables &world)
{
	if(depth <= 0)
	{
		return Color(0, 0, 0);
	}

	Hit_record record;


	if(!world.hit(ray, Interval(0.001, infinity), record))
		return background;

	Color attenuation;
	Ray   scattered_ray;

	Color emission_color = record.material->emitted(	record.u
														, record.v
														, record.hit_point);

	if(!record.material->scattered(ray, record, attenuation, scattered_ray))
		return emission_color;

	Color scatter_color = attenuation * ray_color(	scattered_ray
													, depth - 1
													, world);

	return emission_color + scatter_color;
}


void Camera::open_file(const char *file_name)
{
	image_file = std::ofstream(file_name);

	if(!image_file.is_open())
	{
		throw std::ofstream::failure("Unable to open image_file\n");
	}
}

Ray Camera::get_sample_ray(size_t col, size_t row) const
{
	Vec3 offset = sample_square();

	Point3 sample_pixel = pixel_0_0 +
					(offset.x() + col) * delta_u +
					(offset.y() + row) * delta_v;

	Point3 ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();

	double ray_time = rand_double();

	return Ray(ray_origin, sample_pixel - ray_origin, ray_time);
}

Vec3 Camera::sample_square() const
{
	return Vec3(rand_double() - 0.5, rand_double() - 0.5, 0);
}

Point3 Camera::defocus_disk_sample() const
{
	Vec3 point = rand_in_unit_disk();

	return camera_center + (point[0] * defocus_disk_u) + (point[1] * defocus_disk_v);
}
