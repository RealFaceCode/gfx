#pragma once

#include <vector>
    
namespace gfx
{
    struct Mesh
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> texCoords;
        std::vector<unsigned int> indices;
        uint32_t meshSize;
    };
}