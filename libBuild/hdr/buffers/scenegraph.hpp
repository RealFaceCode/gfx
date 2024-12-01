#pragma once

#include <vector>
#include "mesh.hpp"
#include "material.hpp"
#include "meshanimation.hpp"
#include "scenecamera.hpp"
#include "scenelight.hpp"
#include "scenetexture.hpp"

namespace gfx
{
    struct SceneGraph
    {
        std::vector<Mesh> meshes;
        std::vector<Material> materials;
        std::vector<MeshAnimation> animations;
        std::vector<SceneCamera> cameras;
        std::vector<SceneLight> lights;
        std::vector<SceneTexture> textures;
    };
}