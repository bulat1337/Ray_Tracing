#include "ray_tracing.h"
#include "RT_DSL.h"

void lab()
{
	Scene scene;

	auto gr_sp_tex  = Make_texture::checker(	0.6
												, Color(	255.0 / 255.0
															, 247.0 / 255.0
															, 188.0 / 255.0)
												, Color(	255.0 / 255.0
															, 102.0 / 255.0
															, 178.0 / 255.0));

	double gr_sp_radius = 1000;
	Point3 gr_sp_center(0, -1000, 0);

	scene.add_sphere(gr_sp_center, gr_sp_radius, Make_material::lambertian(gr_sp_tex));

	Camera cam;

	cam.aspect_ratio    = 16.0 / 9.0;
	cam.background      = Color(	186.0 / 255.0
									, 226.0 / 255.0
									, 255.0 / 255.0);
	cam.defocus_angle   = 0;
	cam.focus_dist      = 5;
	cam.diffusion_depth = 50;
	cam.image_width     = 400;
	cam.lookat          = Point3(0.0, 1.0, 0.0);
	cam.lookfrom        = Point3(5.0, 2.0, 0.0);
	// cam.lookfrom        = Point3(5.0, 3.5, -3.0);
	cam.sampling        = 10;
	cam.vertical_FOV    = 55;
	cam.view_up         = Vec3(0, 1, 0);

	cam.render(scene.get_world());
}

void cornell_smoke()
{
    Scene scene;

    auto red   = Make_material::lambertian(Color(.65, .05, .05));
    auto white = Make_material::lambertian(Color(.73, .73, .73));
    auto green = Make_material::lambertian(Color(.12, .45, .15));
    auto light = Make_material::diffuse_light(Color(7, 7, 7));

    scene.add_quad(Point3(555, 0, 0), 	   Vec3(0, 555, 0),  Vec3(0, 0, 555),  green);
    scene.add_quad(Point3(0, 0, 0),  	   Vec3(0, 555, 0),  Vec3(0, 0, 555),  red);
    scene.add_quad(Point3(113, 554, 127),  Vec3(330, 0, 0),  Vec3(0, 0, 305),  light);
    scene.add_quad(Point3(0, 555, 0),      Vec3(555, 0, 0),  Vec3(0, 0, 555),  white);
    scene.add_quad(Point3(0, 0, 0),  	   Vec3(555, 0, 0),  Vec3(0, 0, 555),  white);
    scene.add_quad(Point3(0, 0, 555),      Vec3(555, 0, 0),  Vec3(0, 555, 0),  white);

    std::shared_ptr<Hittable> box1 = Make_hittable::box(Point3(0,0,0), Point3(165,330,165), white);
    box1 = Make_instance::rotate_y (box1, 15);
    box1 = Make_instance::translate(box1, Vec3(265,0,295));

    std::shared_ptr<Hittable> box2 = Make_hittable::box(Point3(0,0,0), Point3(165,165,165), white);
    box2 = Make_instance::rotate_y(box2, -18);
    box2 = Make_instance::translate(box2, Vec3(130,0,65));

    scene.add_constant_medium(box1, 0.01, Color(0,0,0));
    scene.add_constant_medium(box2, 0.01, Color(1,1,1));

    Camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 500;
    cam.sampling = 10;
    cam.diffusion_depth = 50;
    cam.background = Color(0,0,0);

    cam.vertical_FOV = 40;
    cam.lookfrom = Point3(278, 278, -800);
    cam.lookat = Point3(278, 278, 0);
    cam.view_up = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(scene.get_world());
}

void cornell_box()
{
    Scene scene;

    auto red   = Make_material::lambertian(Color(.65, .05, .05));
    auto white = Make_material::lambertian(Color(.73, .73, .73));
    auto green = Make_material::lambertian(Color(.12, .45, .15));

    auto light = Make_material::diffuse_light(Color(15, 15, 15));

    scene.add_quad(	Point3(555, 0, 0)
					, Vec3(0, 555, 0)
					, Vec3(0, 0, 555)
					, green);

    scene.add_quad(	Point3(0, 0, 0)
					, Vec3(0, 555, 0)
					, Vec3(0, 0, 555)
					, red);

    scene.add_quad(	Point3(343, 554, 332)
					, Vec3(-130, 0, 0)
					, Vec3(0, 0, -105)
					, light);

    scene.add_quad(	Point3(0, 0, 0)
					, Vec3(555, 0, 0)
					, Vec3(0, 0, 555)
					, white);

    scene.add_quad(	Point3(555, 555, 555)
					, Vec3(-555, 0, 0)
					, Vec3(0, 0, -555)
					, white);

    scene.add_quad(	Point3(0, 0, 555)
					, Vec3(555, 0, 0)
					, Vec3(0, 555, 0)
					, white);

	std::shared_ptr<Hittable> box_1 = Make_hittable::box(	Point3(0, 0, 0)
															, Point3(165, 330, 165)
															, white);

	box_1 = Make_instance::rotate_y (box_1, 15);
	box_1 = Make_instance::translate(box_1, Vec3(265, 0, 295));
	// scene.add(box_1);

	std::shared_ptr<Hittable> box_2 = Make_hittable::box(	Point3(0, 0, 0)
															, Point3(165, 165, 165)
															, white);

	box_2 = Make_instance::rotate_y (box_2, -18);
	box_2 = Make_instance::translate(box_2, Vec3(130, 0, 65));
	// scene.add(box_2);

	Hittables boxes;
	boxes.add(box_1);
	boxes.add(box_2);

	scene.add_bvh_node(boxes);


    Camera cam;

    cam.aspect_ratio    = 1.0;
    cam.image_width     = 200;
    cam.sampling        = 5;
    cam.diffusion_depth = 2;
    cam.background      = Color(0,0,0);

    cam.vertical_FOV    = 40;
    cam.lookfrom        = Point3(278, 278, -800);
    cam.lookat          = Point3(278, 278, 0);
    cam.view_up         = Vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(scene.get_world());
}

void simple_light()
{
    Scene scene;

    auto pertext = Make_texture::noise(4);

    scene.add_sphere(	Point3(0, -1000, 0)
						, 1000
						, Make_material::lambertian(pertext));

    scene.add_sphere(	Point3(0, 2, 0)
						, 2
						, Make_material::lambertian(pertext));

    auto difflight = Make_material::diffuse_light(Color(4, 4, 4));

	scene.add_sphere(	Point3(0, 5, 0)
						, 1
						, difflight);

    scene.add_quad(	Point3(3, 1, -2)
					, Vec3(2, 0, 0)
					, Vec3(0, 2, 0)
					, difflight);

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

    cam.render(scene.get_world());
}

int main()
{
	// call scene here

	return 0;
}
