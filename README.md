# Ray Traciong

## About

This project is a brute force ray tracing engine, meticulously designed to manually calculate the path of every individual ray as it interacts with a 3D environment. Unlike traditional rendering techniques, this engine follows each ray's journey through the scene, enabling it to produce highly realistic images with detailed effects such as scatterings, reflections, refractions, and shadows. By implementing the ray tracing process from scratch, the project offers a comprehensive exploration of the underlying principles and algorithms, making it a valuable foundation for future developments in photorealistic rendering techniques.

## Key Features

### Oversampling

**Oversampling** is a crucial feature in this brute force ray tracing engine, designed to enhance the final image quality by reducing aliasing and increasing detail. The core idea behind oversampling is that instead of casting a single ray to determine the color of a pixel, multiple rays are cast with slight variations, and their results are averaged to produce a smoother, more accurate color.

**How It Works**:

When the engine renders a pixel, it doesn't rely on just one ray to sample the color. Instead, it sends multiple rays, each slightly offset within the pixel area. This process captures more information about the scene, particularly in areas where there are sharp contrasts or fine details. The more rays used, the better the approximation of the pixel’s true color, resulting in a higher-quality image with reduced noise and smoother gradients.

Users have control over the number of rays, or samples, per pixel via cameras sampling parameter. By increasing the number of samples, the final image becomes more detailed, though this also increases the computational load. This trade-off allows users to balance between rendering time and image quality based on their specific needs.

### Diffusion Depth
Сontrols the maximum number of times a ray can bounce off objects in the scene, affecting how light and color are calculated during rendering. This parameter prevents infinite loops in complex environments by limiting the number of interactions a ray can have before it is terminated.

**How It Works**:

- Rays are cast into the scene, bouncing off surfaces and altering color based on interactions.
- The `diffusion_depth` sets a limit on these bounces. If a ray reaches this limit, it stops contributing to the final image.

**Code Implementation**: In the `Camera` class, the `render` method repeatedly calls the `ray_color` function, passing the current ray and the specified `diffusion_depth`. The `ray_color` function recursively calculates the color by tracing the ray's path, reducing the depth with each bounce. When the depth reaches zero, the ray is terminated, returning black.

This feature allows users to balance rendering quality and performance: higher diffusion depths capture more detailed lighting effects, while lower depths reduce computation time.

### Defocuse Blur

Simulates a depth of field effect by introducing variability in the origin of rays cast from the camera. Instead of originating from a single point, rays are generated from random points within a disk surrounding the camera. This simulates the effect of a camera lens with a specific aperture size, where the size of the disk is controlled by parameters like `defocus_angle` and `focus_dist`.

**How It Works**:

- Rays are cast from points randomly sampled within a disk centered around the camera. The size of this disk, which defines how much the rays are spread, is determined by the `defocus_angle` and `focus_dist` parameters.
- A larger `defocus_angle` or closer `focus_dist` increases the size of the disk, resulting in a more pronounced blur effect, especially for objects not at the focal distance.
- The effect is akin to what you see in photography when objects outside the depth of field appear blurred, while those at the focal plane remain sharp.

### Motion Blur

Introduces the ability to simulate the blurring effect caused by the motion of objects during the rendering process. This is achieved by allowing dynamic objects, such as spheres, to have a starting and ending position, simulating their movement over time. The ray tracer randomly selects positions along the object's path, effectively capturing the motion blur effect as the object transitions from its start to its end position.

**How It Works**:

- Each moving object, like a sphere, is defined with a `start_center` and an `end_center`, representing its position at the beginning and end of the rendering time interval.
- As rays are cast to detect collisions, the object's position is calculated based on a random time point within the rendering interval. This random selection mimics the object being in motion, creating a blur effect in the final rendered image.
- The object's position for each ray is determined by the method `current_center`, which interpolates between `start_center` and `end_center` based on the ray's time value.

**Code Implementation**:
In the `Sphere` class, a moving sphere is initialized with `start_center` and `end_center` points, along with a direction vector (`path_dir`) that defines the movement path. During ray-object intersection tests (`hit`method), the sphere's center is calculated using `current_center`, which considers the motion over time, adding variability to the sphere's position in each rendered frame.

This method captures the natural blur seen when objects move quickly relative to the camera's shutter speed, enhancing the realism of fast-moving objects in the rendered scene.

### BVH Optimization
An optimization technique used to accelerate ray tracing by organizing objects into a tree structure. The key idea is to enclose groups of objects within bounding volumes, allowing for efficient ray intersection tests. Instead of checking every object in the scene, rays are first tested against larger bounding volumes, and only if a ray intersects a bounding volume does it then test against the individual objects inside. This dramatically reduces the number of intersection tests, making rendering faster, especially in complex scenes.

**How It Works**:

- **Bounding Volumes**: A bounding volume is a box that fully encloses one or more objects. The BVH algorithm begins by computing a bounding box for a group of objects.
- **Tree Structure**: The objects are recursively divided into two groups, each enclosed by its own bounding volume, forming the nodes of a binary tree. The process continues until each leaf node contains a single object.
- **Ray Intersection**: When a ray is cast, it first checks for intersection with the bounding volume at the root of the tree. If it misses, the ray can skip all objects in that branch of the tree. If it hits, the ray proceeds to check the child nodes (smaller bounding volumes) down the tree, until it either hits an object or exits the tree.

**Code Implementation**:

- The `BVH_node` constructor recursively builds the BVH tree. It calculates the bounding box for a group of objects, determines the axis along which to split the objects (based on the longest axis of the bounding box), and then sorts the objects along that axis.
- Depending on the number of objects, the group is split into two, and the process is repeated for each group to build the left and right child nodes of the tree.
- During ray tracing, the `BVH_node::hit` method is used to test ray intersections. It first checks if the ray intersects the bounding box. If it does, the method checks the left and right children, allowing the algorithm to efficiently skip large portions of the scene that don't intersect with the ray.

### Texture Mapping and Materials
Critical components in a ray tracing engine that define the appearance and behavior of surfaces. In this implementation, textures control the color of an object at different points on its surface, while materials determine how the object interacts with light, including how it reflects or absorbs light rays.
#### Texture Mapping

1) **Solid Color**: The simplest texture type, where the entire surface is a uniform color.
	The `Solid_color` class stores a single color (`albedo`) and returns this color for any point on the surface.
2) **Checker Texture**: A procedural texture that creates a checkerboard pattern on the surface.
	The `Checker` class alternates between two textures (or colors) based on the surface coordinates.
3) **Image Texture**: Uses an external image file to map colors onto the surface.
	The `Image_texture` class maps the (u, v) coordinates on the surface to pixel coordinates in the image, returning the corresponding color.
4) **Perlin Noise**: A procedural texture that generates a pseudo-random pattern, often used to simulate natural textures like marble or clouds.
	The `Noise` class generates a color pattern based on a mathematical function applied to the surface coordinates.
#### Materials
1) **Lambertian**: Represents a surface that scatters light according to Lambert's cosine law, creating a matte appearance.
	The `Lambertian` class uses a texture to determine the surface color and scatters the incoming ray.
2) **Metal**: Represents a reflective surface with a controllable fuzziness, simulating materials like polished metal or brushed steel.
	The `Metal` class reflects the incoming ray around the surface normal and applies a fuzz factor to scatter the reflection slightly.
3) **Dielectric**: Represents transparent materials like glass or water, capable of refracting rays according to Snell's law.
	The `Dielectric` class calculates whether the ray is reflected or refracted based on the angle of incidence and the material’s refractive index.
4) **Dielectric**: Represents transparent materials like glass or water, capable of refracting rays according to Snell's law.
	The `Dielectric` class calculates whether the ray is reflected or refracted based on the angle of incidence and the material’s refractive index.
5) **Isotropic**: Represents materials that scatter light uniformly in all directions, used for simulating participating media like fog or smoke.
	The `Isotropic` class scatters rays in a random direction and uses a texture for the color attenuation.

### Instances

**How it Works**:

The **Instances** feature enables the creation of transformed versions of existing objects, such as rotated or translated instances, without altering the original geometry. This is achieved by applying mathematical transformations, specifically matrix operations, to the object's coordinates. This approach simplifies object manipulation within a scene, making it easier to create complex arrangements and variations of objects.

- **Rotation**: Objects can be rotated around an axis, typically the Y-axis, by applying a rotation matrix. This changes the object's orientation without modifying its core geometry.
- **Translation**: Objects can be shifted in space by applying a translation vector, allowing them to be positioned differently in the scene.

**Code Implementation**:

The implementation involves two key classes: `Rotate_y` and `Translate`.

- **`Rotate_y`**: Handles rotating an object around the Y-axis. It calculates the object's new bounding box after rotation and modifies ray interactions accordingly, ensuring that rays are correctly aligned with the rotated object.
- **`Translate`**: Manages translating an object by a given offset. It adjusts the object's bounding box and modifies ray interactions to account for the object's new position in space.

These classes allow for flexible manipulation of objects within a ray-traced scene, enabling complex and dynamic scene composition without directly altering the original object geometry.
### Planar Objects

Planar objects represent 2D geometric shapes like quadrilaterals, triangles, and disks, which are defined in a 3D space. These shapes are useful for creating flat surfaces or specific shapes within a 3D scene.

**How it Works**:

Planar objects are created using a plane origin and two vectors that define the plane's orientation. The vectors span the plane, and their cross product gives the plane's normal, which is used to calculate intersections with rays. The intersection point is then checked to see if it lies within the boundaries of the shape.

Quadrilaterals are defined by two vectors that form the sides of the shape. Disks are similar but also have a radius constraint to define the circular boundary. Triangles use a different inside check based on barycentric coordinates.

**Code Implementation**:

The implementation begins with the `Planar` class, which sets up the basic structure for a planar object, including calculating its normal and setting its bounding box. Specific shapes like quadrilaterals, disks, and triangles extend from this base class, each with its own method for checking if a hit point lies within the boundaries of the shape.
## Installation

**Clone** the repository using the following command in a directory of your choice:

```

git clone git@github.com:bulat1337/Ray_Tracing.git

```
## Usage
### If you want to render example scenes:

1) Navigate to the `examples/build` folder:
```
cd examples/build
```

2) Build the project:
```
cmake ..
make
```

3) The executable will be located in the `build` folder that you are currently in. You can run it without leaving the `build` folder by executing:
```
../example
```
The rendering process will begin, and the rendering time report will be output to `std::clog`.

4) The rendered scene will be saved in the `image.ppm` file located in the `build` directory where you are currently located.
You can also use the `build_script` script to build the project and run the executable:
```
./build_script
```

If you encounter permission issues, you can modify the permissions of the `lan_sc` script by running the following command while in the `build` folder:
```
chmod +rwx build_script
```
### If you want to implement ray tracing in your project:
1) Navigate to the `build` folder:
```
cd build
```

2) Build the project:
```
cmake ..
make
```
3) Include the header:
```
#include "ray_tracing.h"
```
4) Link `libray_tracing.a`

If you are building your project using CMake, simply use `add_subdirectory` to include and build the ray tracer recursively.
## System specs
**CPU**: Apple M1
**RAM**: 8 GB
**OS**: MacOS 14.6
**Compiler**: Apple clang version 14.0.3

