#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <fstream>
#include <chrono>

#include "color.h"
#include "ray.h"
#include "utils.h"
#include "hittables.h"
#include "material.h"

class Camera
{
  public:
	double aspect_ratio		= 1;
	size_t image_width 		= 400;
	size_t sampling			= 1;
	size_t diffusion_depth	= 10;
	double vertical_FOV     = 90;
	Color  background;

	Point3 lookfrom         = Point3(0, 0, 0);
	Point3 lookat           = Point3(0, 0, -1);
	Vec3   view_up          = Vec3(0, 1, 0);

	double defocus_angle = 0;
	double focus_dist    = 10;

	Camera();

	void render(const Hittables world);

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

	void initialize();

	Color ray_color(const Ray &ray, size_t depth, const Hittables &world);

	void open_file(const char *file_name);

	Ray get_sample_ray(size_t col, size_t row) const;

	Vec3 sample_square() const;

	Point3 defocus_disk_sample() const;
};

#endif
