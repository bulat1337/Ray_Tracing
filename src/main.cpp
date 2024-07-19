// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"

int main()
{
	Camera camera;

// image width and aspect_ratio
	camera.image_width     = 400;
	camera.aspect_ratio    = 16.0 / 9.0;
	camera.sampling        = 100;
	camera.diffusion_depth = 50;

	camera.vertical_FOV = 90;
	camera.lookfrom = Point3(-2, 2, 1);
	camera.lookat   = Point3(0, 0, -1);
	camera.view_up  = Vec3(0, 1, 0);

// world
	Hittables world;

//scene2
	auto material_ground    = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center    = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left      = std::make_shared<Dielectric>(1.5);
	auto material_bubble    = std::make_shared<Dielectric>(1.0 / 1.5);
	auto material_right     = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.9);
	// auto material_secondary = std::make_shared<Metal>(Color(0.1, 0.2, 0.3), 0.2);

	world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
	world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

	// world.add(std::make_shared<Sphere>(Point3( 0.7,    0.7, -0.5),   0.2, material_secondary));
	// world.add(std::make_shared<Sphere>(Point3( 0.8,    -0.3, -0.5),   0.1, material_secondary));
	// world.add(std::make_shared<Sphere>(Point3( -0.4,    1.0, -0.5),   0.3, material_secondary));


//scene 2
// 	auto R = std::cos(pi / 4);
//
// 	auto material_left  = std::make_shared<Lambertian>(Color(0, 0, 1));
// 	auto material_right = std::make_shared<Lambertian>(Color(1, 0, 0));
//
// 	world.add(std::make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
// 	world.add(std::make_shared<Sphere>(Point3(R, 0, -1), R,  material_right));



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
