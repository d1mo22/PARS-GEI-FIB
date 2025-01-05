#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix, modelViewMatrix;
uniform mat3 normalMatrix;

uniform sampler2D positionMap;
uniform sampler2D normalMap1;

uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

uniform int mode = 3;

vec4 light(vec3 N, vec3 V, vec3 L, vec3 P) {
    vec3 R = reflect(-L, N);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R, V));
    float Ispec = 0;
    if (NdotL > 0) Ispec = pow(RdotV, matShininess);

    vec4 diffuse = matDiffuse;
    if (mode == 3) diffuse = vec4(P,1.0);

    return lightAmbient * matAmbient +
    diffuse * lightDiffuse * NdotL +
    matSpecular * lightSpecular * Ispec;

}

void main() {

    vec2 st = vec2(
        0.004 + ((vertex.x + 1) / 2) * (0.996 -0.004),
        0.004 + ((vertex.y + 1) / 2) * (0.996 -0.004)
    );

    vec3 vertexPrima = texture(positionMap, st).rgb;
    vec3 normalPrima = texture(normalMap1, st).rgb;
    normalPrima = normalPrima * 2 - 1;

    vec3 P = normalize((modelViewMatrix * vec4(vertexPrima,1.0)).xyz);
    vec3 V = normalize(-P);
    vec3 L = normalize(lightPosition.xyz - P);
    vec3 N = normalize(normalMatrix * normalPrima);
    switch (mode) {
        case 0:
            frontColor = vec4(vertexPrima, 1.0);
            break;
        case 1:
            frontColor = vec4(vertexPrima, 1.0) * N.z;
            break;
        case 2:
            frontColor = light(V, N, L, (vertexPrima)) * N.z;
            break;
        case 3:
            frontColor = light(V, N, L, (vertexPrima)) * N.z;
            break;


    }
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertexPrima, 1.0);
}
