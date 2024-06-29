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

    void SetShader2(Shader* shader);
    Shader* GetShader2() const;

    void SetPropertyVec3(const std::string& name, glm::vec3 value);
    const std::map<std::string, glm::vec3>& GetPropertiesVec3() const;

    void SetPropertyFloat(const std::string& name, float value);
    const std::map<std::string, float>& GetPropertiesFloat() const;

    void AddTexture(unsigned int textureID);
    const std::vector<unsigned int> GetTextureIDs() const;

private:
    Shader* mShader{};
    Shader* mShader2{};
    std::map<std::string, glm::vec3> mPropertiesVec3{};
    std::map<std::string, unsigned int> mPropertiesUInt{};
    std::map<std::string, float> mPropertiesFloat{};
    std::vector<unsigned int> mTextureIDs{};
};