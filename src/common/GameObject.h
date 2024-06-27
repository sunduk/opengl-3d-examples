#pragma once

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

// forward declaration.
class Line;
class Material;
class Mesh;
class SimpleMesh;

class GameObject
{
public:
    GameObject();
    GameObject(unsigned int instanceId);
    virtual ~GameObject();

    void SetMesh(Mesh* mesh);
    void SetLine(Line* line);
    void SetMaterial(Material* material);
    unsigned int GetInstanceId();
    void Update(const ShaderParam& shaderParam, float deltaSec);
    void DrawMesh();

private:
    void SetMaterialProperties(Shader* shader, const ShaderParam& shaderParam);

public:
    Transform mTransform{};

private:
    unsigned int mInstanceId{};

    Mesh* mMesh{};
    Line* mLine{};
    Material* mMaterial{};
};