// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"

int main()
{
	Camera camera;

// image width and aspect_ratio
	camera.image_width  = 600;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.sampling = 100;
	camera.diffusion_depth = 50;

// world
	Hittables world;

	auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
	auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

	world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));


// render

	try
	{
		camera.render(world);
	}
	catch(const std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
	}



	return 0;
}
