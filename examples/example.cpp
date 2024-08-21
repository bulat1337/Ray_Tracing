#include <iostream>

#include "ray_tracing.h"

void lab()
{
	Hittables world;

	using std::shared_ptr;
	using std::make_shared;

// --------------------------~ Ground ~----------------------------------------------

	auto gr_sp_tex  = std::make_shared<Checker>(	0.6
													, Color(	255.0 / 255.0
																, 247.0 / 255.0
																, 188.0 / 255.0)
													, Color(	255.0 / 255.0
																, 102.0 / 255.0
																, 178.0 / 255.0));

	shared_ptr<Material> gr_sp_mat = make_shared<Lambertian>(gr_sp_tex);
	double gr_sp_radius = 1000;
	Point3 gr_sp_center(0, -1000, 0);

	shared_ptr<Sphere>gr_sp = make_shared<Sphere>(	gr_sp_center
													, gr_sp_radius
													, gr_sp_mat);
	world.add(gr_sp);

// ----------—----------—----------—----------—----------—----------—----------—---

// --------------------------~ Sphere ~----------------------------------------------

// 	auto tester_sp_tex  = std::make_shared<Image_texture>("mercury.jpg");
//
// 	shared_ptr<Material> tester_sp_mat = make_shared<Lambertian>(tester_sp_tex);
//
// 	double tester_sp_radius = 1;
//
// 	Point3 tester_sp_center_begin(0, 1, 0);
//
// 	shared_ptr<Sphere>tester_sp = make_shared<Sphere>(	tester_sp_center_begin
// 														, tester_sp_radius
// 														, tester_sp_mat);

// ----------—----------—----------—----------—----------—----------—----------—---

// --------------------------~ Triangle ~----------------------------------------------


Color triangle_albedo(	24.0 / 255.0
						, 200.0 / 255.0
						, 180.4 / 255.0);

auto triangle_mat = std::make_shared<Lambertian>(triangle_albedo);

auto triangle = std::make_shared<Triangle>(	Point3(0.0, 0.1, 1.5)
											, Point3(0.0, 2.0, 1.0)
											, Point3(0.0, 0.0, 2.0)
											, triangle_mat);

world.add(triangle);

// --------------------------------------------------------------------------------

// --------------------------~ Disk ~----------------------------------------------


Color disk_albedo(	24.0 / 255.0
					, 100.0 / 255.0
					, 240.4 / 255.0);

auto disk_mat = std::make_shared<Lambertian>(disk_albedo);

auto disk = std::make_shared<Disk>(	Point3(0.0, 1.1, 0.0)
									, Point3(0.0, 0.0, 1.0)
									, Point3(0.0, 1.0, 0.0)
									, disk_mat
									, 1.0);

world.add(disk);

// --------------------------------------------------------------------------------

// --------------------------~ Quad ~----------------------------------------------


Color quad_albedo(	240.0 / 255.0
					, 200.0 / 255.0
					, 80.4 / 255.0);

auto quad_mat = std::make_shared<Lambertian>(quad_albedo);

auto quad = std::make_shared<Quad>(	Point3(0.0, 0.1, -1.5)
									, Point3(0.0, 0.0, -2.0)
									, Point3(0.0, 2.0, 0.0)
									, quad_mat);

world.add(quad);
// --------------------------------------------------------------------------------

// --------------------------~ Wall ~----------------------------------------------

// 	Color wall_albedo(	40.0    / 255.0
// 							, 40.0 / 255.0
// 							, 40.0 / 255.0);
//
// 	shared_ptr<Material> wall_mat = make_shared<Lambertian>(wall_albedo);
//
// 	Point3 wall_orig(-3, 0, 5);
//
// 	Vec3 wall_u( 0, 0, -10);
// 	Vec3 wall_v( 0, 10,   0);
//
// 	shared_ptr<Quad> wall = make_shared<Quad>(	wall_orig
// 												, wall_u
// 												, wall_v
// 												, wall_mat);

// --------------------------------------------------------------------------------



// --------------------------~ Box ~----------------------------------------------

// 	Color tester_box_albedo(	164.0 / 255.0
// 								, 84.0 / 255.0
// 								, 255.0 / 255.0);
//
// 	shared_ptr<Material> tester_box_mat = make_shared<Metal>(tester_box_albedo, 0.0);
//
// 	Point3 box_corner(1.0, 0.0, -2.0);
// 	Point3 offset_vec(-2, 2, -2);
//
// 	shared_ptr<Hittable> tester_box = create_box(	box_corner
// 											, box_corner + offset_vec
// 											, tester_box_mat);

// --------------------------------------------------------------------------------

// --------------------------~ Light ~----------------------------------------------

// 	Point3 light_quad_orig(1.75, 1.75, 1.75);
//
// 	Vec3 light_quad_u(-1, 1, -1);
// 	Vec3 light_quad_v( 1, 0, -1);
//
//
//
// 	Color light_quad_emit(	255.0 / 255.0
// 							, 222.0 / 255.0
// 							, 84.0  / 255.0);
//
// 	shared_ptr<Material> light_quad_mat = make_shared<Diffuse_light>(light_quad_emit);
//
// 	shared_ptr<Quad> light_quad = make_shared<Quad>(	light_quad_orig
// 														, light_quad_u
// 														, light_quad_v
// 														, light_quad_mat);

// --------------------------~ Camera ~----------------------------------------------


	Camera cam;

	cam.aspect_ratio    = 16.0 / 9.0;
	cam.background      = Color(	186.0 / 255.0
									, 226.0 / 255.0
									, 255.0 / 255.0);
	cam.defocus_angle   = 0;
	cam.focus_dist      = 5;
	cam.diffusion_depth = 50;
	cam.image_width     = 1000;
	cam.lookat          = Point3(0.0, 1.0, 0.0);
	cam.lookfrom        = Point3(5.0, 2.0, 0.0);
	// cam.lookfrom        = Point3(5.0, 3.5, -3.0);
	cam.sampling        = 1000;
	cam.vertical_FOV    = 55;
	cam.view_up         = Vec3(0, 1, 0);


	cam.render(world);
}

void final_scene(int image_width, int samples_per_pixel, int max_depth)
{
    Hittables boxes1;
    auto ground = std::make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;

    for (int i = 0; i < boxes_per_side; i++)
	{
        for (int j = 0; j < boxes_per_side; j++)
		{
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = rand_double(1, 101);
            auto z1 = z0 + w;

            boxes1.add(create_box(Point3(x0, y0, z0), Point3(x1, y1, z1), ground));
        }
    }

    Hittables world;

    world.add(std::make_shared<BVH_node>(boxes1));

    auto light = std::make_shared<Diffuse_light>(Color(7, 7, 7));

    world.add(std::make_shared<Quad>(	Point3(123,554,147)
										, Vec3(300,0,0)
										, Vec3(0,0,265)
										, light));

    auto center1 = Point3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    auto Sphere_material = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.1));

    world.add(std::make_shared<Sphere>(center1, center2, 50, Sphere_material));

    world.add(	std::make_shared<Sphere>(Point3(260, 150, 45)
				, 50
				, std::make_shared<Dielectric>(1.5)));

    world.add(	std::make_shared<Sphere>(Point3(0, 150, 145)
				, 50
				, std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)));

    auto boundary = std::make_shared<Sphere>(	Point3(360,150,145)
												, 70
												, std::make_shared<Dielectric>(1.5));
    world.add(boundary);
    world.add(std::make_shared<Constant_medium>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
    boundary = std::make_shared<Sphere>(Point3(0,0,0), 5000, std::make_shared<Dielectric>(1.5));
    world.add(std::make_shared<Constant_medium>(boundary, .0001, Color(1,1,1)));

    auto emat = std::make_shared<Lambertian>(std::make_shared<Image_texture>("earthmap.jpg"));
    world.add(std::make_shared<Sphere>(Point3(400,200,400), 100, emat));
    auto pertext = std::make_shared<Noise>(0.2);
    world.add(std::make_shared<Sphere>(Point3(220,280,300), 80, std::make_shared<Lambertian>(pertext)));

    Hittables boxes2;

    auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
    int ns = 1000;

    for (int j = 0; j < ns; j++)
	{
        boxes2.add(std::make_shared<Sphere>(Point3::random(0, 165), 10, white));
    }

	world.add(std::make_shared<Translate>(
				std::make_shared<Rotate_y>(
					std::make_shared<BVH_node>(boxes2), 15)
					, Vec3(-100, 270, 395)
		));

	Camera cam;

	cam.aspect_ratio      = 1.0;
	cam.image_width       = image_width;
	cam.sampling 		  = samples_per_pixel;
	cam.diffusion_depth   = max_depth;
	cam.background        = Color(0,0,0);

	cam.vertical_FOV      = 40;
	cam.lookfrom          = Point3(478, 278, -600);
	cam.lookat            = Point3(278, 278, 0);
	cam.view_up           = Vec3(0,1,0);

	cam.defocus_angle     = 0;

	cam.render(world);

}


void cornell_smoke()
{
    Hittables world;

    auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = std::make_shared<Diffuse_light>(Color(7, 7, 7));

    world.add(std::make_shared<Quad>(Point3(555,0,0), Vec3(0,555,0), Vec3(0,0,555), green));
    world.add(std::make_shared<Quad>(Point3(0,0,0), Vec3(0,555,0), Vec3(0,0,555), red));
    world.add(std::make_shared<Quad>(Point3(113,554,127), Vec3(330,0,0), Vec3(0,0,305), light));
    world.add(std::make_shared<Quad>(Point3(0,555,0), Vec3(555,0,0), Vec3(0,0,555), white));
    world.add(std::make_shared<Quad>(Point3(0,0,0), Vec3(555,0,0), Vec3(0,0,555), white));
    world.add(std::make_shared<Quad>(Point3(0,0,555), Vec3(555,0,0), Vec3(0,555,0), white));

    std::shared_ptr<Hittable> box1 = create_box(Point3(0,0,0), Point3(165,330,165), white);
    box1 = std::make_shared<Rotate_y>(box1, 15);
    box1 = std::make_shared<Translate>(box1, Vec3(265,0,295));

    std::shared_ptr<Hittable> box2 = create_box(Point3(0,0,0), Point3(165,165,165), white);
    box2 = std::make_shared<Rotate_y>(box2, -18);
    box2 = std::make_shared<Translate>(box2, Vec3(130,0,65));

    world.add(std::make_shared<Constant_medium>(box1, 0.01, Color(0,0,0)));
    world.add(std::make_shared<Constant_medium>(box2, 0.01, Color(1,1,1)));

    Camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 500;
    cam.sampling = 1000;
    cam.diffusion_depth = 50;
    cam.background = Color(0,0,0);

    cam.vertical_FOV = 40;
    cam.lookfrom = Point3(278, 278, -800);
    cam.lookat = Point3(278, 278, 0);
    cam.view_up = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


void cornell_create_box()
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

	std::shared_ptr<Hittable> box_1 = create_box(	Point3(0, 0, 0)
											, Point3(165, 330, 165)
											, white);

	box_1 = std::make_shared<Rotate_y> (box_1, 15);
	box_1 = std::make_shared<Translate>(box_1, Vec3(265, 0, 295));
	// world.add(box_1);

	std::shared_ptr<Hittable> box_2 = create_box(	Point3(0, 0, 0)
											, Point3(165, 165, 165)
											, white);

	box_2 = std::make_shared<Rotate_y> (box_2, -18);
	box_2 = std::make_shared<Translate>(box_2, Vec3(130, 0, 65));
	// world.add(box_2);


    Camera cam;

    cam.aspect_ratio    = 1.0;
    cam.image_width     = 500;
    cam.sampling        = 500;
    cam.diffusion_depth = 2;
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


void perlin_Spheres()
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

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = rand_double();
			Point3 center(a + 0.9 * rand_double(), 0.2, b + 0.9 * rand_double());

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

	// world = Hittables(std::make_shared<BVH_node>(world)); // BVH

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.sampling = 50;
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

void checkered_Spheres()
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
	, CORNELL_SMOKE
	, FINAL_SCENE
	, LAB
};


int main()
{
	Scene scene = Scene::FINAL_SCENE;

	switch (scene)
	{
		case Scene::BOOK_COVER:
			book_cover();
			break;
		case Scene::CHECKERED:
			checkered_Spheres();
			break;
		case Scene::EARTH:
			earth();
			break;
		case Scene::PERLIN:
			perlin_Spheres();
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
			cornell_create_box();
			break;
		case Scene::CORNELL_SMOKE:
			cornell_smoke();
			break;
		case Scene::FINAL_SCENE:
			final_scene(100, 3, 50);
			break;
		case Scene::LAB:
			lab();
			break;
		default:
			std::cout << "Unknown scene\n";
	}


	return 0;
}
