#include "ray_tracing.h"

#include <string>

class Scene
{
  private:
	static size_t scene_counter;
	Hittables world;

  public:
	std::string name = "Scene_" + std::to_string(scene_counter);

	Scene()
	{
		++scene_counter;
	}

	Scene(const std::string &_name):
		name(_name)
	{
		++scene_counter;
	}

	const Hittables &get_world() { return world; }

	Scene &bvh_optimization_on()
	{
		world = Hittables(std::make_shared<BVH_node>(world));
	}

	Scene &add(const std::shared_ptr<Hittable> hittable)
	{
		world.add(hittable);

		return *this;
	}

	Scene &add_sphere(	const Point3 &start_center
						, double radius
						, std::shared_ptr<Material> material)
	{
		std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(	start_center
																	, radius
																	, material);
		world.add(sphere);

		return *this;
	}

	Scene &add_sphere(	const Point3 &start_center
						, const Point3 &end_center
						, double radius
						, std::shared_ptr<Material> material)
	{
		std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(	start_center
																	, end_center
																	, radius
																	, material);
		world.add(sphere);

		return *this;
	}

	Scene &add_quad(const Point3 &plane_orig
					, const Vec3 &u
					, const Vec3 &v
					, std::shared_ptr<Material> material)
	{
		std::shared_ptr<Quad> quad = std::make_shared<Quad>(plane_orig
															, u
															, v
															, material);
		world.add(quad);

		return *this;
	}

	Scene &add_disk(const Point3 &plane_orig
					, const Vec3 &u
					, const Vec3 &v
					, std::shared_ptr<Material> material
					, double radius)
	{
		std::shared_ptr<Disk> disk = std::make_shared<Disk>(plane_orig
															, u
															, v
															, material
															, radius);
		world.add(disk);

		return *this;
	}

	Scene &add_triangle(const Point3 &plane_orig
						, const Vec3 &u
						, const Vec3 &v
						, std::shared_ptr<Material> material)
	{
		std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(plane_orig
																		, u
																		, v
																		, material);
		world.add(triangle);

		return *this;
	}

	Scene &add_constant_medium(	std::shared_ptr<Hittable> boundary
								, double density
								, std::shared_ptr<Texture> texture)
	{
		std::shared_ptr<Constant_medium> constant_medium
			= std::make_shared<Constant_medium>(boundary
												, density
												, texture);
		world.add(constant_medium);

		return *this;
	}

	Scene &add_constant_medium(	std::shared_ptr<Hittable> boundary
								, double density
								, const Color &albedo)
	{
		std::shared_ptr<Constant_medium> constant_medium
			= std::make_shared<Constant_medium>(boundary
												, density
												, albedo);
		world.add(constant_medium);

		return *this;
	}

	Scene &add_bvh_node(const Hittables &hittables)
	{
		std::shared_ptr<BVH_node> bvh_node = std::make_shared<BVH_node>(hittables);

		world.add(bvh_node);

		return *this;
	}
};

size_t Scene::scene_counter = 0;

class Make_hittable
{
  public:
	static std::shared_ptr<Sphere> sphere(	const Point3 &start_center
											, double radius
											, std::shared_ptr<Material> material)
	{
		return std::make_shared<Sphere>(	start_center
											, radius
											, material);
	}

	static std::shared_ptr<Sphere> sphere(	const Point3 &start_center
											, const Point3 &end_center
											, double radius
											, std::shared_ptr<Material> material)
	{
		return std::make_shared<Sphere>(	start_center
											, end_center
											, radius
											, material);
	}

	static std::shared_ptr<Quad> quad(	const Point3 &plane_orig
										, const Vec3 &u
										, const Vec3 &v
										, std::shared_ptr<Material> material)
	{
		return std::make_shared<Quad>(	plane_orig
										, u
										, v
										, material);
	}

	static std::shared_ptr<Disk> disk(	const Point3 &plane_orig
										, const Vec3 &u
										, const Vec3 &v
										, std::shared_ptr<Material> material
										, double radius)
	{
		return std::make_shared<Disk>(	plane_orig
										, u
										, v
										, material
										, radius);
	}

	static std::shared_ptr<Triangle> triangle(	const Point3 &plane_orig
												, const Vec3 &u
												, const Vec3 &v
												, std::shared_ptr<Material> material)
	{
		return std::make_shared<Triangle>(	plane_orig
											, u
											, v
											, material);
	}

	static std::shared_ptr<Hittables> box(	const Point3 &a
											, const Point3 &b
											, std::shared_ptr<Material> material)
	{
		return create_box(a, b, material);
	}

	static std::shared_ptr<BVH_node> bvh_node(const Hittables &hittables)
	{
		return std::make_shared<BVH_node>(hittables);
	}
};

class Make_instance
{
  public:
	static std::shared_ptr<Translate> translate(	std::shared_ptr<Hittable> object
													, const Vec3 &offset)
	{
		return std::make_shared<Translate>(object, offset);
	}

	static std::shared_ptr<Rotate_y> rotate_y(std::shared_ptr<Hittable> object, double angle)
	{
		return std::make_shared<Rotate_y>(object, angle);
	}
};

class Make_material
{
  public:
	static std::shared_ptr<Lambertian> lambertian(const Color &albedo)
	{
		return std::make_shared<Lambertian>(albedo);
	}

	static std::shared_ptr<Lambertian> lambertian(std::shared_ptr<Texture> texture)
	{
		return std::make_shared<Lambertian>(texture);
	}

	static std::shared_ptr<Metal> metal(const Color &albedo, double fuzz)
	{
		return std::make_shared<Metal>(albedo, fuzz);
	}

	static std::shared_ptr<Dielectric> dielectric(double refraction_id)
	{
		return std::make_shared<Dielectric>(refraction_id);
	}

	static std::shared_ptr<Diffuse_light> diffuse_light(std::shared_ptr<Texture> texture)
	{
		return std::make_shared<Diffuse_light>(texture);
	}

	static std::shared_ptr<Diffuse_light> diffuse_light(const Color& emit)
	{
		return std::make_shared<Diffuse_light>(emit);
	}

	static std::shared_ptr<Isotropic> isotropic(const Color &albedo)
	{
		return std::make_shared<Isotropic>(albedo);
	}

	static std::shared_ptr<Isotropic> isotropic(std::shared_ptr<Texture> texture)
	{
		return std::make_shared<Isotropic>(texture);
	}
};

class Make_texture
{
  public:
	static std::shared_ptr<Checker> checker(double scale
											, std::shared_ptr<Texture> even
											, std::shared_ptr<Texture> odd)
	{
		return std::make_shared<Checker>(scale, even, odd);
	}

	static std::shared_ptr<Checker> checker(double scale
											, const Color &even
											, const Color &odd)
	{
		return std::make_shared<Checker>(scale, even, odd);
	}

	static std::shared_ptr<Solid_color> solid_color(const Color &albedo)
	{
		return std::make_shared<Solid_color>(albedo);
	}

	static std::shared_ptr<Solid_color> solid_color(double red, double green, double blue)
	{
		return std::make_shared<Solid_color>(red, green, blue);
	}

	static std::shared_ptr<Image_texture> image_texture(const char *file_name)
	{
		return std::make_shared<Image_texture>(file_name);
	}

	static std::shared_ptr<Noise> noise(double scale)
	{
		return std::make_shared<Noise>(scale);
	}
};

