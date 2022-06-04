#pragma once
#include <cstdint>

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8;

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

    Image& colorMask(float r, float g, float b);

    Image& encodeMessage(const char* message);
    Image& decodeMessage(char* buffer, size_t* messageLength);
};