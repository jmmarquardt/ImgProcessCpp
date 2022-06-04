#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
// #include <string.h>
#include "stb_image.h"
#include "stb_image_write.h"

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
    image_type type = get_file_type(filename);
    int success = 0;
    switch (type)
    {
        case png:
            success = stbi_write_png(filename, width, height, channels, data, width * channels);
            break;
        case jpg:
            success = stbi_write_jpg(filename, width, height, channels, data, 100);
            break;
        case bmp:
            success = stbi_write_bmp(filename, width, height, channels, data);
            break;
        case tga:
            success = stbi_write_tga(filename, width, height, channels, data);
            break;
    }
    return success != 0;
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

Image& Image::grayscale_avg()
{
    // average the rgb values
    if (channels > 3)
        printf("Image %p is monochromatic, dichromatic, or blank. It cannot be converted to grayscale.", this);
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
            memset(data + i, gray, 3);
        }
    }
    return *this;
}

Image& Image::grayscale_lum()
{
    // weighted average of rgb values to preserve luminance value
    if (channels < 3)
    {
        printf("Image %p is monochromatic, dichromatic, or blank. It cannot be converted to grayscale.", this);
    }
    else
    {
        // CIE 1931 luminance coefficients
        const float rLum = 0.2126f;
        const float gLum = 0.7152f;
        const float bLum = 0.0722f;

        for (int i = 0; i < size; i += channels)
        {
            int gray = rLum * data[i] + gLum * data[i + 1] + bLum * data[i + 2];
            memset(data + i, gray, 3);
        }
        return *this;
    }
}

Image& Image::colorMask(float r, float g, float b)
{
    if (channels < 3)
    {
        printf("\e[31m[ERROR] Color mask requires at least 3 channels, but this image has %d channels\e[0m\n", channels);
    }
    else
    {
        for (int i = 0; i < size; i += channels)
        {
            data[i] *= r;
            data[i + 1] *= g;
            data[i + 2] *= b;
        }
    }
    return *this;
}

Image& Image::encodeMessage(const char* message)
{
    uint32_t len = strlen(message) * sizeof(char);
    for (uint8_t i = 0; i < STEG_HEADER_SIZE; ++i)
    {
        data[i] &= 0xFE;
        data[i] |= (len >> (STEG_HEADER_SIZE - 1 - i)) & 1UL;
    }

    return *this;
}

Image& Image::decodeMessage(char* buffer, size_t* messageLength)
{
    uint32_t len = 0;
    for (uint8_t i = 0; i < STEG_HEADER_SIZE; ++i)
    {
        len = (len<<1) | (data[i] & 1);
    }
}
