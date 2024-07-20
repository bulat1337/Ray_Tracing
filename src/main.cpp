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

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = get_random();
			Point3 center(a + 0.9*get_random(), 0.2, b + 0.9*get_random());

			if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_Material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = Color::random() * Color::random();
					sphere_Material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_Material));
				} else if (choose_mat < 0.95) {
					// Metal
					auto albedo = Color::random(0.5, 1);
					auto fuzz = get_random(0, 0.5);
					sphere_Material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_Material));
				} else {
					// glass
					sphere_Material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_Material));
				}
			}
		}
	}

	auto Material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, Material1));

	auto Material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, Material2));

	auto Material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, Material3));

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.sampling = 100;
	cam.diffusion_depth = 50;

	cam.vertical_FOV = 20;
	cam.lookfrom = Point3(13,2,3);
	cam.lookat = Point3(0,0,0);
	cam.view_up = Vec3(0,1,0);

	cam.defocus_angle = 0.6;
	cam.focus_dist = 10.0;


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
