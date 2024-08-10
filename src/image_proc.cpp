#ifdef _MSC_VER
    #pragma warning (push, 0)
#endif


#define STB_IMAGE_IMPLEMENTATION
// // #define STB_IMAGE_STATIC
// #define STBI_FAILURE_USERMSG
// #define STBI_ASSERT(x)
#include "image_proc.h"

#include <cstdlib>
#include <iostream>



External_img::External_img() {}

External_img::External_img(const char* image_filename)
{
	auto filename = std::string(image_filename);
	auto imagedir = getenv("RTW_IMAGES");

	if (imagedir && load(std::string(imagedir) + "/" + image_filename)) return;
	if (load(filename)) return;
	if (load("images/" + filename)) return;
	if (load("../images/" + filename)) return;
	if (load("../../images/" + filename)) return;
	if (load("../../../images/" + filename)) return;
	if (load("../../../../images/" + filename)) return;
	if (load("../../../../../images/" + filename)) return;
	if (load("../../../../../../images/" + filename)) return;

	std::cerr << "ERROR: Could not load image file '" << image_filename << "'.\n";
}

External_img::~External_img()
{
	delete[] bdata;
	STBI_FREE(fdata);
}

bool External_img::load(const std::string& filename)
{
	auto n = bytes_per_pixel; // Dummy out parameter: original components per pixel
	fdata = stbi_loadf(filename.c_str(), &image_width, &image_height, &n, bytes_per_pixel);
	if (fdata == nullptr) return false;

	bytes_per_scanline = image_width * bytes_per_pixel;
	convert_to_bytes();
	return true;
}

int External_img::width()  const { return (fdata == nullptr) ? 0 : image_width; }
int External_img::height() const { return (fdata == nullptr) ? 0 : image_height; }

const unsigned char* External_img::pixel_data(int x, int y) const
{
	static unsigned char magenta[] = { 255, 0, 255 };
	if (bdata == nullptr) return magenta;

	x = clamp(x, 0, image_width);
	y = clamp(y, 0, image_height);

	return bdata + y*bytes_per_scanline + x*bytes_per_pixel;
}

int External_img::clamp(int x, int low, int high)
{
	if (x < low) return low;
	if (x < high) return x;
	return high - 1;
}

unsigned char External_img::float_to_byte(float value)
{
	if (value <= 0.0)
		return 0;
	if (1.0 <= value)
		return 255;
	return static_cast< unsigned char >(256.0 * value);
}

void External_img::convert_to_bytes()
{
	int total_bytes = image_width * image_height * bytes_per_pixel;
	bdata = new unsigned char[total_bytes];

	auto *bptr = bdata;
	auto *fptr = fdata;
	for (auto i=0; i < total_bytes; i++, fptr++, bptr++)
	{
		*bptr = float_to_byte(*fptr);
	}
}

#ifdef _MSC_VER
    #pragma warning (pop)
#endif