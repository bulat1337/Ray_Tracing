// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "bvh.hpp"

int main()
{
	Camera cam;
	Hittables world;

	auto checker = std::make_shared<Checker>(	0.32
												, Color(0.2, 0.3, 0.1)
												, Color(0.9, 0.9, 0.9));

	world.add(std::make_shared<Sphere>(	Point3(0, -1000, 0)
										, 1000
										, std::make_shared<Lambertian>(checker)));

	for (int a = -3; a < 3; a++) {
		for (int b = -3; b < 3; b++) {
			auto choose_mat = rand_double();
			Point3 center(a + 0.9*rand_double(), 0.2, b + 0.9*rand_double());

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
					auto fuzz = rand_double(0, 0.5);
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
	world.add(std::make_shared<Sphere>(Point3(-4, 0.9, 0), 1.0, Material2));

	auto Material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, Material3));

	world = Hittables(std::make_shared<BVH_node>(world));

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.sampling = 25;
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
