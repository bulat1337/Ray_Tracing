// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"

int main()
{
	Camera cam;
	Hittables world;

	auto ground_Material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_Material));

	auto Material1 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3(0, 1, 0), Point3(-1, 1, -1), 1.0, Material1));

	// auto Material2 = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.9));
	// world.add(std::make_shared<Sphere>(Point3(-3, 1, -1.5), 1.0, Material2));

	// auto Material3 = std::make_shared<Lambertian>(Color(0.9, 0.8, 0.3));
	// world.add(std::make_shared<Sphere>(Point3(3, 1, 1.5), 1.0, Material3));

	// auto Material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	// world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, Material3));

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 600;
	cam.sampling = 50;
	cam.diffusion_depth = 50;

	cam.vertical_FOV = 50;

	cam.lookfrom = Point3(5, 1, 0);

	cam.lookat = Point3(0, 1, 0);

	cam.view_up = Vec3(0,1,0);


	cam.defocus_angle = 0;
	cam.focus_dist = 5;


	try
	{
		cam.render(world);
	}
	catch(const std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
	}



	return 0;
}
