#version 330 core

in vec3 Normal;
in vec4 VertexWorldPosition;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 customColor;
uniform vec3 cameraWorldPosition;

out vec4 Color;

void main()
{
    // ���� ����Ʈ ���� ����.
    vec3 normal = normalize(Normal);
    float brightness = max(dot(lightDirection, -normal) * 0.5f + 0.5f, 0);
    brightness = pow(brightness, 2);
    vec3 diffuse = brightness * lightColor * customColor;

    // ���� �ȼ����� ī�޶�� ���ϴ� ���͸� ���Ѵ�.
    vec3 vertexToCamera = normalize(cameraWorldPosition - VertexWorldPosition.xyz);

    // �׵θ� ���� ���Ѵ�. ������ ������� 1���� ���ִ� ������ �׵θ��� ������ rim���� 1�� ������ ����� ���ؼ��̴�.
    float rim = 1 - max(dot(vertexToCamera, normal), 0);

    // ������ �ŵ������� �Ͽ� �׵θ����� �̻ڰ� ����� �ش�.
    rim = pow(rim, 4);
    
    // �׵θ��� ����� ������ �����Ѵ�.
    vec3 yellow = vec3(1,1,0);
    vec3 rimColor = yellow * rim;

    // ���� ���꿡�� ���� ����� ���ϱ� ������ �Ͽ� ���� ������ �����Ѵ�.
    Color = vec4(diffuse + rimColor, 1);
}