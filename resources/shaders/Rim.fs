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
    // 하프 램버트 조명 연산.
    vec3 normal = normalize(Normal);
    float brightness = max(dot(lightDirection, -normal) * 0.5f + 0.5f, 0);
    brightness = pow(brightness, 2);
    vec3 diffuse = brightness * lightColor * customColor;

    // 현재 픽셀에서 카메라로 향하는 벡터를 구한다.
    vec3 vertexToCamera = normalize(cameraWorldPosition - VertexWorldPosition.xyz);

    // 테두리 값을 구한다. 내적의 결과값을 1에서 빼주는 이유는 테두리로 갈수록 rim값을 1에 가깝게 만들기 위해서이다.
    float rim = 1 - max(dot(vertexToCamera, normal), 0);

    // 적당히 거듭제곱을 하여 테두리값을 이쁘게 만들어 준다.
    rim = pow(rim, 4);
    
    // 테두리로 사용할 색상을 결정한다.
    vec3 yellow = vec3(1,1,0);
    vec3 rimColor = yellow * rim;

    // 조명 연산에서 나온 결과와 더하기 연산을 하여 최종 색상을 결정한다.
    Color = vec4(diffuse + rimColor, 1);
}