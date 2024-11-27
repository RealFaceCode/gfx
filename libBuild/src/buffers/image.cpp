#include "buffers/image.hpp"

namespace gfx
{
    Image::Image()
    : data(nullptr), size(0), channels(0) {}

    Image::Image(uint8_t* data, int width, int height, int channels, bool flip)
    {
        setData(data, width, height, channels, flip);
    }

    Image::Image(const Image& other)
    : data(other.data), size(other.size), channels(other.channels) {}

    Image::Image(Image&& other)
    : data(other.data), size(other.size), channels(other.channels)
    {
        other.data = nullptr;
        other.size = glm::vec2(0);
        other.channels = 0;
    }

    Image& Image::operator=(Image&& other)
    {
        data = other.data;
        size = other.size;
        channels = other.channels;
        other.data = nullptr;
        other.size = glm::vec2(0);
        other.channels = 0;
        return *this;
    }

    Image::~Image()
    {
        if (data != nullptr)
            delete[] data;
    }

    void Image::setData(uint8_t* data, int width, int height, int channels, bool flip)
    {
        if (this->data != nullptr)
            delete[] this->data;

        this->data = data;
        size = glm::vec2(width, height);
        this->channels = channels;

        if (flip)
        {
            uint8_t* temp = new uint8_t[width * height * channels];
            
            for (int y = 0; y < height; y++)
                memcpy(temp + (y * width * channels), data + ((height - y - 1) * width * channels), width * channels);

            delete[] data;
            this->data = temp;
        }
    }

    const uint8_t* Image::getData() const
    {
        return data;
    }

    const glm::vec2& Image::getSize() const
    {
        return size;
    }

    const int& Image::getChannels() const
    {
        return channels;
    }
}