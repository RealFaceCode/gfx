#include "meshloader.hpp"

#include <assimp/config.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <lc.hpp>

namespace gfx
{
    static Mesh processMesh(aiMesh* mesh)
    {
        Mesh m;
        m.vertices.reserve(mesh->mNumVertices * 3);
        m.normals.reserve(mesh->mNumVertices * 3);
        if(mesh->mTextureCoords[0])
            m.texCoords.reserve(mesh->mNumVertices * 2);
        if(mesh->HasFaces())
            m.indices.reserve(mesh->mNumFaces * 3);
        m.meshSize = mesh->mNumVertices;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            if(mesh->HasPositions())
            {
                m.vertices.emplace_back(mesh->mVertices[i].x);
                m.vertices.emplace_back(mesh->mVertices[i].y);
                m.vertices.emplace_back(mesh->mVertices[i].z);
            }

            if(mesh->HasNormals())
            {
                m.normals.emplace_back(mesh->mNormals[i].x);
                m.normals.emplace_back(mesh->mNormals[i].y);
                m.normals.emplace_back(mesh->mNormals[i].z);
            }

            if(mesh->mTextureCoords[0])
            {
                m.texCoords.emplace_back(mesh->mTextureCoords[0][i].x);
                m.texCoords.emplace_back(mesh->mTextureCoords[0][i].y);
            }
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                m.indices.emplace_back(face.mIndices[j]);
        }

        return m;
    }

    static Material processMaterial(const ::aiMaterial* material)
    {
        Material m;
        aiColor4D color(0.0f, 0.0f, 0.0f, 1.0f);

        ::aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
        m.ambient = glm::vec3(color.r, color.g, color.b);

        ::aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
        m.diffuse = glm::vec3(color.r, color.g, color.b);

        ::aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
        m.specular = glm::vec3(color.r, color.g, color.b);

        float shininess;
        ::aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
        m.shininess = shininess;

        return m;
    }

    static MeshAnimation processAnimation(const ::aiAnimation* animation)
    {
        MeshAnimation a;
        a.name = animation->mName.C_Str();
        a.duration = animation->mDuration;
        a.ticksPerSecond = animation->mTicksPerSecond;

        for(unsigned int i = 0; i < animation->mNumChannels; i++)
        {
            const ::aiNodeAnim* channel = animation->mChannels[i];
            std::vector<glm::mat4> keyFrames;
            for(unsigned int j = 0; j < channel->mNumPositionKeys; j++)
            {
                aiVectorKey key = channel->mPositionKeys[j];
                glm::vec3 position(key.mValue.x, key.mValue.y, key.mValue.z);
                keyFrames.emplace_back(translate(glm::mat4(1.0f), position));
            }
            for(unsigned int j = 0; j < channel->mNumRotationKeys; j++)
            {
                aiQuatKey key = channel->mRotationKeys[j];
                glm::quat rotation(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z);
                keyFrames.emplace_back(glm::toMat4(rotation));
            }
            for(unsigned int j = 0; j < channel->mNumScalingKeys; j++)
            {
                aiVectorKey key = channel->mScalingKeys[j];
                glm::vec3 scale(key.mValue.x, key.mValue.y, key.mValue.z);
                keyFrames.emplace_back(glm::scale(glm::mat4(1.0f), scale));
            }
            a.channels.emplace_back(channel->mNodeName.C_Str(), keyFrames);
        }

        return a;
    }

    static SceneCamera processCamera(const ::aiCamera* camera)
    {
        SceneCamera c;
        c.position = glm::vec3(camera->mPosition.x, camera->mPosition.y, camera->mPosition.z);
        c.lookAt = glm::vec3(camera->mLookAt.x, camera->mLookAt.y, camera->mLookAt.z);
        c.up = glm::vec3(camera->mUp.x, camera->mUp.y, camera->mUp.z);
        c.aspect = camera->mAspect;
        c.near = camera->mClipPlaneNear;
        c.far = camera->mClipPlaneFar;
        c.fov = camera->mHorizontalFOV;
        c.orthoWidth = camera->mOrthographicWidth;
        c.name = camera->mName.C_Str();
        return c;
    }

    static SceneLight processLight(const ::aiLight* light)
    {
        SceneLight l;
        l.name = light->mName.C_Str();

        switch(light->mType)
        {
            using enum gfx::SceneLightType;
            case aiLightSourceType::aiLightSource_DIRECTIONAL:
                l.type = DIRECTIONAL;
                break;
            case aiLightSourceType::aiLightSource_POINT:
                l.type = POINT;
                break;
            case aiLightSourceType::aiLightSource_SPOT:
                l.type = SPOT;
                break;
            default:
                l.type = DIRECTIONAL;
                break;
        }

        l.position = glm::vec3(light->mPosition.x, light->mPosition.y, light->mPosition.z);
        l.direction = glm::vec3(light->mDirection.x, light->mDirection.y, light->mDirection.z);
        l.up = glm::vec3(light->mUp.x, light->mUp.y, light->mUp.z);

        l.attenuationConstant = light->mAttenuationConstant;
        l.attenuationLinear = light->mAttenuationLinear;
        l.attenuationQuadratic = light->mAttenuationQuadratic;

        l.colorDiffuse = glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b);
        l.colorSpecular = glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b);
        l.colorAmbient = glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b);

        l.angleInnerCone = light->mAngleInnerCone;
        l.angleOuterCone = light->mAngleOuterCone;

        l.size = glm::vec2(light->mSize.x, light->mSize.y);
        return l;
    }

    static SceneTexture processTexture(const ::aiTexture* texture)
    {
        SceneTexture t;
        t.path = texture->mFilename.C_Str();
        t.type = texture->achFormatHint;
        t.width = texture->mWidth;
        t.height = texture->mHeight;
        return t;
    }

    static SceneGraph processModel(const aiScene* scene)
    {
        SceneGraph sg;

        for(unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            sg.meshes.emplace_back(processMesh(scene->mMeshes[i]));
        }

        for(unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            sg.materials.emplace_back(processMaterial(scene->mMaterials[i]));
        }

        for(unsigned int i = 0; i < scene->mNumAnimations; i++)
        {
            sg.animations.emplace_back(processAnimation(scene->mAnimations[i]));
        }

        for(unsigned int i = 0; i < scene->mNumCameras; i++)
        {
            sg.cameras.emplace_back(processCamera(scene->mCameras[i]));
        }

        for(unsigned int i = 0; i < scene->mNumLights; i++)
        {
            sg.lights.emplace_back(processLight(scene->mLights[i]));
        }

        for(unsigned int i = 0; i < scene->mNumTextures; i++)
        {
            sg.textures.emplace_back(processTexture(scene->mTextures[i]));
        }

        return sg;
    }

    MeshLoader::MeshLoader(uint32_t flags)
        : postProcessing(flags)
    {
    }

    SceneGraph MeshLoader::loadMesh(const char* path, bool logInfo)
    {
        const aiScene* scene = importer.ReadFile(path, postProcessing);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            lc::Log<gfx::GL>("ERROR", "Failed to load model");
            return {};
        }

        lc::Log<gfx::GL>("INFO", "Model loaded successfully: {}", path);
        if(logInfo)
        {
            lc::Log<gfx::GL>("INFO", "Number of meshes: {}", scene->mNumMeshes);
            lc::Log<gfx::GL>("INFO", "Number of materials: {}", scene->mNumMaterials);
            lc::Log<gfx::GL>("INFO", "Number of animations: {}", scene->mNumAnimations);
            lc::Log<gfx::GL>("INFO", "Number of textures: {}", scene->mNumTextures);
            lc::Log<gfx::GL>("INFO", "Number of cameras: {}", scene->mNumCameras);
            lc::Log<gfx::GL>("INFO", "Number of lights: {}", scene->mNumLights);
        }

        SceneGraph sg = processModel(scene);
        importer.FreeScene();
        return sg;
    }

    void MeshLoader::setPostProcessing(uint32_t flags)
    {
        postProcessing = flags;
    }

    void MeshLoader::setPropertyBool(const char* name, bool value)
    {
        importer.SetPropertyBool(name, value);
    }

    void MeshLoader::setPropertyInt(const char* name, int value)
    {
        importer.SetPropertyInteger(name, value);
    }

    void MeshLoader::setPropertyFloat(const char* name, float value)
    {
        importer.SetPropertyFloat(name, value);
    }

    void MeshLoader::setPropertyString(const char* name, const char* value)
    {
        importer.SetPropertyString(name, value);
    }
}