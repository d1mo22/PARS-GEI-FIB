#version 330 core

in vec4 frontColor;
in vec3 fvertex;
in vec3 fnormal;

out vec4 fragColor;

uniform vec4 matAmbient, matDiffuse;
uniform vec4 lightAmbient, lightDiffuse;
uniform vec4 lightPosition;
uniform mat3 normalMatrix;

vec4 light(vec3 N, vec3 L) {
    float NdotL = max(0.0,dot(N,L));
    return (matAmbient * lightAmbient + 
    matDiffuse * lightDiffuse * NdotL);
}


void main() {

    vec3 L = normalize(lightPosition.xyz - fvertex);
    vec3 N = normalize(cross(dFdx(fvertex), dFdy(fvertex)));
    //vec3 N = normalize(fnormal);
    fragColor = frontColor*light(N,L);
}
