// #include <iostream>

#include "camera.hpp"
#include "sphere.hpp"

int main()
{
	Camera camera;

// image width and aspect_ratio
	camera.image_width  = 400;
	camera.aspect_ratio = 16.0 / 9.0;

// world
	Hittables world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));

	world.add(std::make_shared<Sphere>(Point3(1, 0, -0.5), 0.1));
	world.add(std::make_shared<Sphere>(Point3(0.5, 0.1, -0.5), 0.1));
	world.add(std::make_shared<Sphere>(Point3(0.4, -0.2, -0.5), 0.1));
	world.add(std::make_shared<Sphere>(Point3(-0.3, 0.3, -0.5), 0.1));

	world.add(std::make_shared<Sphere>(Point3(0.75, 0.75, -1), 0.25));
	world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

// render

	try
	{
		camera.render(world);
	}
	catch(const std::exception exception)
	{
		std::cerr << exception.what() << std::endl;
	}



	return 0;
}
