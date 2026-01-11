#version 330 core

in vec4 frontColor;
in vec3 P;
in vec3 N;
out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular;
uniform int n;

const float pi = acos(-1.0);

vec4 light(vec3 V, vec3 L) {
    vec3 R = normalize(2.0*dot(N,L)*N-L);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R,V));
    float Ispec = 0;
    if (NdotL > 0) Ispec = pow(RdotV, matShininess);
    return 
    (matDiffuse * lightDiffuse * NdotL)/sqrt(n) +
    matSpecular * lightSpecular * Ispec;

}

void main() {
    vec3 V = normalize(-P);
    vec3 color = vec3(0.0);
    for (int i = 0; i < n; ++i) {
        float angle = 2.0 * pi * float(i) / float(n);
        vec3 lightPos = vec3(10.0 * cos(angle), 10.0 * sin(angle), 0.0);
        vec3 L = normalize(lightPos - P);

        color += light(V, L).xyz;
    }

    fragColor = vec4(color, 1.0);
}
