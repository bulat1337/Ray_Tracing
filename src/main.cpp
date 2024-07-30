// #include <iostream>

#include "material.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "bvh.hpp"
#include "planar.hpp"

void cornell_box()
{
    Hittables world;

    auto red   = std::make_shared<Lambertian>(		Color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(		Color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(		Color(.12, .45, .15));
    auto light = std::make_shared<Diffuse_light>(	Color(15, 15, 15));

    world.add(std::make_shared<Quad>(	Point3(555, 0,   0)
										, Vec3(0,   555, 0)
										, Vec3(0,   0,   555)
										, green));
    world.add(std::make_shared<Quad>(	Point3(0, 0,   0)
										, Vec3(0, 555, 0)
										, Vec3(0, 0,   555)
										, red));

    world.add(std::make_shared<Quad>(	Point3(343,  554, 332)
										, Vec3(-130, 0,   0)
										, Vec3(0,    0,   -105)
										, light));

    world.add(std::make_shared<Quad>(	Point3(0,   0, 0)
										, Vec3(555, 0, 0)
										, Vec3(0,   0, 555)
										, white));

    world.add(std::make_shared<Quad>(	Point3(555,  555, 555)
										, Vec3(-555, 0,   0)
										, Vec3(0,    0,   -555)
										, white));

    world.add(std::make_shared<Quad>(	Point3(0,   0,   555)
										, Vec3(555, 0,   0)
										, Vec3(0,   555, 0)
										, white));

	world.add(box(	Point3(130, 0, 65)
					, Point3(295, 265, 230)
					, white));

	world.add(box(	Point3(265, 0, 295)
					, Point3(430, 330, 460)
					, white));

    Camera cam;

    cam.aspect_ratio    = 1.0;
    cam.image_width     = 300;
    cam.sampling        = 25;
    cam.diffusion_depth = 50;
    cam.background      = Color(0,0,0);

    cam.vertical_FOV    = 40;
    cam.lookfrom        = Point3(278, 278, -800);
    cam.lookat          = Point3(278, 278, 0);
    cam.view_up         = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


void simple_light()
{
    Hittables world;

    auto pertext = std::make_shared<Noise>(4);

    world.add(	std::make_shared<Sphere>(Point3(0,-1000,0)
				, 1000
				, std::make_shared<Lambertian>(pertext)));

    world.add(std::make_shared<Sphere>(	Point3(0,2,0)
										, 2
										, std::make_shared<Lambertian>(pertext)));

    auto difflight = std::make_shared<Diffuse_light>(Color(4,4,4));

	world.add(	std::make_shared<Sphere>(Point3(0, 5, 0)
				, 1
				, difflight));

    world.add(	std::make_shared<Quad>(Point3(3,1,-2)
				, Vec3(2,0,0)
				, Vec3(0,2,0)
				, difflight));

    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.sampling = 100;
    cam.diffusion_depth = 50;
    cam.background = Color(0,0,0);

    cam.vertical_FOV = 20;
    cam.lookfrom = Point3(26,3,6);
    cam.lookat = Point3(0,2,0);
    cam.view_up = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


void triangles()
{
	Hittables world;

	std::shared_ptr<Lambertian> triag_mat = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));


	world.add(std::make_shared<Triangle>(	Point3(0, 0, 0)
											, Point3(5, 3, 0)
											, Point3(0, 7, 0)
											, triag_mat));

	world.add(std::make_shared<Triangle>(	Point3(0, 0, 0)
											, Point3(-5, -3, 0)
											, Point3(0, -7, 0)
											, triag_mat));

	Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.sampling = 25;
    cam.diffusion_depth = 50;
	cam.background = Color(0.7, 0.8, 1.0);

    cam.vertical_FOV = 80;
    cam.lookfrom = Point3(0, 0, 13);
    cam.lookat = Point3(0, 0, 0);
    cam.view_up = Vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void disks()
{
	Hittables world;

	std::shared_ptr<Lambertian> disk_mat = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));


	world.add(std::make_shared<Disk>(	Point3(0, 0, 0)
										, Point3(1, -1, 0)
										, Point3(0, 1, 1)
										, disk_mat
										, 2));

	Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.sampling = 25;
    cam.diffusion_depth = 50;
	cam.background = Color(0.7, 0.8, 1.0);

    cam.vertical_FOV = 80;
    cam.lookfrom = Point3(0, 0, 5);
    cam.lookat = Point3(0, 0, 0);
    cam.view_up = Vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void quads()
{
    Hittables world;

    // Materials
    auto left_red    = std::make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto back_green  = std::make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto right_blue  = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto upper_orange = std::make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal  = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    // Quads
    world.add(std::make_shared<Quad>(Point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    world.add(std::make_shared<Quad>(Point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    world.add(std::make_shared<Quad>(Point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    world.add(std::make_shared<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    world.add(std::make_shared<Quad>(Point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    Camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 400;
    cam.sampling = 25;
    cam.diffusion_depth = 50;
	cam.background = Color(0.7, 0.8, 1.0);

    cam.vertical_FOV = 80;
    cam.lookfrom = Point3(0, 0, 9);
    cam.lookat = Point3(0, 0, 0);
    cam.view_up = Vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}


void perlin_spheres()
{
	std::shared_ptr<Noise> perlin_texture = std::make_shared<Noise>(4);

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
	cam.background = Color(0.7, 0.8, 1.0);

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
	cam.background = Color(0.7, 0.8, 1.0);

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
	cam.background = Color(0.7, 0.8, 1.0);

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
	cam.background = Color(0.7, 0.8, 1.0);

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
	, QUADS
	, DISKS
	, TRIANGLES
	, SIMPLE_LIGHT
	, CORNELL
};


int main()
{
	Scene scene = Scene::CORNELL;

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
		case Scene::QUADS:
			quads();
			break;
		case Scene::DISKS:
			disks();
			break;
		case Scene::TRIANGLES:
			triangles();
			break;
		case Scene::SIMPLE_LIGHT:
			simple_light();
			break;
		case Scene::CORNELL:
			cornell_box();
			break;
		default:
			std::cout << "Unknown scene\n";
	}


	return 0;
}
