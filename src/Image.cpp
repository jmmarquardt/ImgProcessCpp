#include "Image.h"

#include <string.h>

#include "stb_image.h"
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

Image::Image(const char* filename)
{
    bool fileRead = read(filename);
    if (fileRead)
    {
        printf("Read %s\n", filename);
        size = width * height * channels;
    }
    else
    {
        printf("Failed to read %s\n", filename);
    }
}

Image::Image(int width, int height, int channels) : width(width), height(height), channels(channels)
{
    size = width * height * channels;
    data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.width, img.height, img.channels)
{
    _memccpy(data, img.data, channels, size);
}

Image::~Image()
{
    stbi_image_free(data);
}

bool Image::read(const char* filename)
{
    data = stbi_load(filename, &width, &height,  &channels, 0);
    
    return data != NULL;
}

bool Image::write(const char* filename)
{
    return false;
}

image_type Image::get_file_type(const char* filename)
{
    const char* extension = strrchr(filename, '.');
    if (extension != nullptr)
    {
        if (strcmp(extension, ".png") == 0)
            return png;
        if (strcmp(extension, ".jpg") == 0)
            return jpg;
        if (strcmp(extension, ".bmp") == 0)
            return bmp;
        if (strcmp(extension, ".tga") == 0)
            return tga;
    }
    return png;
}



