#pragma once

#include "defines.hpp"
#include "buffers/scenegraph.hpp"
#include <assimp/Importer.hpp>

namespace gfx
{
    enum MeshPostProcessingFlag
    {
        CALC_TANGENT_SPACE = 0x1,
        JOIN_IDENTICAL_VERTICES = 0x2,
        MAKE_LEFT_HANDED = 0x4,
        TRIANGULATE = 0x8,
        REMOVE_COMPONENT = 0x10,
        GEN_NORMALS = 0x20,
        GEN_SMOOTH_NORMALS = 0x40,
        SPLIT_LARGE_MESHES = 0x80,
        PRE_TRANSFORM_VERTICES = 0x100,
        LIMIT_BONE_WEIGHTS = 0x200,
        VALIDATE_DATA_STRUCTURE = 0x400,
        IMPROVE_CACHE_LOCALITY = 0x800,
        REMOVE_REDUNDANT_MATERIALS = 0x1000,
        FIX_INFACING_NORMALS = 0x2000,
        SORT_BY_PTYPE = 0x8000,
        FIND_INVALID_DATA = 0x10000,
        GEN_UV_COORDS = 0x20000,
        TRANSFORM_UV_COORDS = 0x40000,
        FIND_INSTANCES = 0x80000,
        OPTIMIZE_MESHES = 0x100000,
        OPTIMIZE_GRAPH = 0x200000,
        FLIP_UV = 0x400000,
        FLIP_WINDING_ORDER = 0x800000,
        SPLIT_BY_BONE_COUNT = 0x1000000,
        DEBONE = 0x2000000,
        GLOBAL_SCALE = 0x4000000,
        EMBED_TEXTURES = 0x8000000,
        FORCE_GEN_NORMALS = 0x10000000,
        DROP_NORMALS = 0x20000000,
        GEN_BOUNDING_BOXES = 0x40000000,
        DEBONE_LIMIT = 0x1FFFFFFF
    };

    class GFX_API MeshLoader
    {
    public:
        MeshLoader() = default;
        explicit MeshLoader(uint32_t flags);
        ~MeshLoader() = default;

        SceneGraph loadMesh(const char* path, bool logInfo = false);
        void setPostProcessing(uint32_t flags);
        void setPropertyBool(const char* name, bool value);
        void setPropertyInt(const char* name, int value);
        void setPropertyFloat(const char* name, float value);
        void setPropertyString(const char* name, const char* value);

    private:
        Assimp::Importer importer;
        uint32_t postProcessing;
    };
}