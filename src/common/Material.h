#pragma once

#include <map>
#include <string>
#include <vector>

#include "glm/glm.hpp"

// forward declaration.
class Shader;

class Material
{
public:
    Material();
    virtual ~Material();

    void SetShader(Shader* shader);
    Shader* GetShader() const;

    void SetPropertyVec3(const std::string& name, glm::vec3 value);
    const std::map<std::string, glm::vec3>& GetPropertiesVec3() const;

    void AddTexture(unsigned int textureID);
    const std::vector<unsigned int> GetTextureIDs() const;

private:
    Shader* mShader{};
    std::map<std::string, glm::vec3> mPropertiesVec3{};
    std::map<std::string, unsigned int> mPropertiesUInt{};
    std::vector<unsigned int> mTextureIDs{};
};