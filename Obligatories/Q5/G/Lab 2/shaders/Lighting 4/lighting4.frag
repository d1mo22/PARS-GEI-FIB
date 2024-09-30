#version 330 core

in vec4 frontColor;
in vec3 P;
in vec3 N;
out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;
uniform vec4 lightPosition; //eye space

vec4 light(vec3 V, vec3 L) {
    vec3 R = normalize(2.0*dot(N,L)*N-L);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R,V));
    float Ispec = 0;
    if (NdotL > 0) Ispec = pow(RdotV, matShininess);
    return matAmbient * lightAmbient +
    matDiffuse * lightDiffuse * NdotL +
    matSpecular * lightSpecular * Ispec;

}

void main()
{
    vec3 L = normalize(lightPosition.xyz - P);
    vec3 V = normalize(-P);
    fragColor = light(V, L);
}
