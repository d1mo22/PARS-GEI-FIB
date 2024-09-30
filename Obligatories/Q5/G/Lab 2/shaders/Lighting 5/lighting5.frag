#version 330 core


in vec4 frontColor;
in vec3 Neye;
in vec3 Veye;
in vec3 Leye;
in vec3 Nworld;
in vec3 Lworld;
in vec3 Vworld;
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform bool world;


vec4 light(vec3 N, vec3 V, vec3 L) {
    N=normalize(N); V=normalize(V); L=normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow(RdotV, matShininess );
    return
    matAmbient * lightAmbient +
    matDiffuse * lightDiffuse * Idiff+
    matSpecular * lightSpecular * Ispec;
    }


void main() {
    if(world)fragColor = light(Nworld,Vworld,Lworld);
    else fragColor = light(Neye,Veye,Leye);
}