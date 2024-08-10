#ifndef IMAGE_PROC_H
#define IMAGE_PROC_H

#include "stb_image.h"

#include <cstdlib>
#include <iostream>


class External_img
{
  public:
    External_img();

    External_img(const char* image_filename);

    ~External_img();

    bool load(const std::string& filename);

    int width()  const;
    int height() const;

    const unsigned char* pixel_data(int x, int y) const;

  private:
    const int      bytes_per_pixel = 3;
    float         *fdata = nullptr;
    unsigned char *bdata = nullptr;
    int            image_width = 0;
    int            image_height = 0;
    int            bytes_per_scanline = 0;

    static int clamp(int x, int low, int high);

    static unsigned char float_to_byte(float value);

    void convert_to_bytes();
};


#endif
