#version 330 core

in vec4 frontColor;
in vec3 fvertex, fnormal;
in vec3 V;

out vec4 fragColor;

uniform vec3 boundingBoxMax, boundingBoxMin;
uniform float matShininess;
uniform vec4 matDiffuse, lightDiffuse, matSpecular, lightSpecular;

vec4 light(vec3 N, vec3 L) {
    vec3 R = normalize(2.0*dot(N,L)*N-L);
    float NdotL = max(0.0,dot(N,L));
    float RdotV =  max(0.0, dot(R,V));
    float Ispec = 0.0;
    if (NdotL > 0) Ispec = pow(RdotV, matShininess);

    vec4 diffuse = (lightDiffuse * matDiffuse * NdotL)/2;
    vec4 specular = lightSpecular * matSpecular * Ispec;

    return diffuse + specular;
}

void main()
{
    vec3 lightPos[8];
    lightPos[0] = boundingBoxMin;
    lightPos[1] = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
    lightPos[2] = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
    lightPos[3] = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
    lightPos[4] = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
    lightPos[5] = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
    lightPos[6] = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
    lightPos[7] = boundingBoxMax;

    vec3 N = normalize(fnormal);
    vec3 color = vec3(0.0);
    for (int i = 0; i < 8; ++i) {
        vec3 L = normalize(lightPos[i] - fvertex);
        color += light(N, L).xyz;
    }
    
    fragColor = vec4(color,1.0);
}
