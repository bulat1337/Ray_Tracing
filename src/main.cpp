// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "bvh.hpp"

void perlin_spheres()
{
	std::shared_ptr<Noise> perlin_texture = std::make_shared<Noise>();

	Point3 ground_sp_center(0, -1000, 0);
	double ground_sp_radius = 1000;

	Point3 main_sp_center(0, 2, 0);
	double main_sp_radius = 2;

	std::shared_ptr<Lambertian> sp_material = std::make_shared<Lambertian>(perlin_texture);

	std::shared_ptr<Sphere> ground_sp = std::make_shared<Sphere>(	ground_sp_center
																		, ground_sp_radius
																		, sp_material);
	std::shared_ptr<Sphere> main_sp   = std::make_shared<Sphere>(	main_sp_center
																		, main_sp_radius
																		, sp_material);

	Hittables world;

	world.add(ground_sp);
	world.add(main_sp);

	Camera cam;

	cam.aspect_ratio 	= 16.0 / 9.0;
	cam.image_width 	= 400;
	cam.sampling 		= 100;
	cam.diffusion_depth = 50;

	cam.vertical_FOV 	= 20;
	cam.lookfrom 		= Point3(13, 2, 3);
	cam.lookat 			= Point3(0, 0, 0);
	cam.view_up 		= Vec3(0, 1, 0);

	cam.defocus_angle = 0.0;

	cam.render(world);
}

void earth()
{
    auto earth_texture = std::make_shared<Image_texture>("earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    auto globe = std::make_shared<Sphere>(Point3(0,0,0), 2, earth_surface);

    Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.sampling = 25;
	cam.diffusion_depth = 50;

	cam.vertical_FOV = 20;
	cam.lookfrom = Point3(0, 0, 12);
	cam.lookat = Point3(0,0,0);
	cam.view_up = Vec3(0,1,0);

	cam.defocus_angle = 0.0;

    cam.render(Hittables(globe));
}


void book_cover()
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
				std::shared_ptr<Material> Sphere_Material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = Color::random() * Color::random();
					Sphere_Material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
				}
				else if (choose_mat < 0.95) {
					// Metal
					auto albedo = Color::random(0.5, 1);
					auto fuzz = rand_double(0, 0.5);
					Sphere_Material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
				}
				else {
					// glass
					Sphere_Material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
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
}

void checkered_spheres()
{
    Hittables world;

    auto checker = std::make_shared<Checker>(	0.32
												, Color(0.2, 0.3, 0.1)
												, Color(0.9, 0.9, 0.9));

    world.add(std::make_shared<Sphere>(	Point3(0, -10, 0)
										, 10
										, std::make_shared<Lambertian>(checker)));
    world.add(std::make_shared<Sphere>(	Point3(0, 10, 0)
										, 10
										, std::make_shared<Lambertian>(checker)));

    Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.sampling = 25;
	cam.diffusion_depth = 50;

	cam.vertical_FOV = 20;
	cam.lookfrom = Point3(13,2,3);
	cam.lookat = Point3(0,0,0);
	cam.view_up = Vec3(0,1,0);

	cam.defocus_angle = 0;

    cam.render(world);
}

enum class Scene
{
	BOOK_COVER
	, CHECKERED
	, EARTH
	, PERLIN
};


int main()
{
	Scene scene = Scene::PERLIN;

	switch (scene)
	{
		case Scene::BOOK_COVER:
			book_cover();
			break;
		case Scene::CHECKERED:
			checkered_spheres();
			break;
		case Scene::EARTH:
			earth();
			break;
		case Scene::PERLIN:
			perlin_spheres();
			break;
		default:
			std::cout << "Unknown scene\n";
	}


	return 0;
}
