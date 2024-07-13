#include <fstream>

#include "color.hpp"
#include "ray.hpp"

Color ray_color(const Ray &ray)
{
	Vec3 unit_dir = unit_vector(ray.direction());

	// std::cout << "units y coord: " << unit_dir.y() << std::endl;

	double coeff = 0.5 * (unit_dir.y() + 1);

	Color start_color(1, 1, 1);
	Color end_color(0.5, 0.7, 1.0);

	return (1 - coeff) * start_color + coeff * end_color;
}

int main()
{
// file
	std::ofstream image_file("image.ppm");

	if(!image_file.is_open())
	{
		throw std::ofstream::failure("Unable to open image_file\n");
	}

// image width and height
	const double aspect_ratio	= 16.0 / 9.0;
	size_t image_width  		= 400;

	size_t image_height = static_cast<size_t>(image_width / aspect_ratio);

	if(image_height < 1)
	{
		image_height = 1;
	}

// camera
	double focal_length = 5.0;

	double viewport_height = 2.0;
	double viewport_width  = viewport_height * (image_width / image_height);

	Point3 camera_center(0, 0, 0);

// axes
	Vec3 viewport_u(viewport_width, 0, 0);
	Vec3 viewport_v(0, -viewport_height, 0);

// deltas
	Vec3 pixel_delta_u = viewport_u / image_width;
	Vec3 pixel_delta_v = viewport_v / image_height;

// starts
	Point3 viewport_upper_left =
		camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	Point3 pixel_0_0 = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


//render
	image_file << "P3\n";

	image_file << image_width << ' ' << image_height << "\n";

	image_file << "255\n";


	std::clog << "Render start.\n" << std::flush;

	for(size_t row = 0 ; row < image_width ; ++row)
	{
		std::clog << "loading row: " << row << '\n' << std::flush;

		for(size_t col = 0 ; col < image_height ; ++col)
		{
			// auto pixel_color = Color(	static_cast<double>(col) / (image_height - 1),
			// 							static_cast<double>(row) / (image_width  - 1),
			// 							0);

			Point3 pixel_center = pixel_0_0 + row * (pixel_delta_v) + col * (pixel_delta_u);

			Vec3 ray_dir = pixel_center - camera_center;

			Ray ray(camera_center, ray_dir);

			auto pixel_color = ray_color(ray);

			print_color(image_file, pixel_color);
		}
	}

	std::clog << "Render end.\n" << std::flush;



	return 0;
}
