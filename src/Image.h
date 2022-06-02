#pragma once
#include <cstdint>

enum image_type
{
    png, jpg, bmp, tga
};

struct Image
{
    uint8_t* data = nullptr;
    size_t size = 0;
    int width;
    int height;
    int channels;

    Image(const char* filename);
    Image(int width, int height, int channels);
    Image(const Image& img);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename);

    image_type get_file_type(const char* filename);

    Image& grayscale_avg();
    Image& grayscale_lum();
};