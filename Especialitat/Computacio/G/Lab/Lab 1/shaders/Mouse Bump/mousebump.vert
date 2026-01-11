#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform int test;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform vec2 mousePosition;
uniform float radius = 300;
uniform vec2 viewport;

vec2 getMousePositionWindowSpace() {
    if(test == 0) return mousePosition;
    if(test == 1) return vec2(400,520);
    if(test == 2) return vec2(600,225);
    if(test == 3) return vec2(200,375);
    return vec2(400,300);
}

//Pasa de coordenadas de objeto a coordenadas de ventana
vec2 windowSpacePos(vec3 P) {
    vec4 clipSpacePos = modelViewProjectionMatrix * vec4(P, 1.0);
    vec2 projectedPos = clipSpacePos.xy / clipSpacePos.w;
    //Pasa de el rango ([-1,-1],[1,1]) a ([0,0],[viewport])
    return (projectedPos + 1.0) / 2.0 * viewport;
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec3 P = vertex;

    float d = distance(getMousePositionWindowSpace(), windowSpacePos(P));
    float t = smoothstep(0.8, 0.05, d/radius);

    vec3 PP = P + normal * 0.03 * distance(boundingBoxMin, boundingBoxMax);
    vec3 finalVertex = mix(P, PP, t);   
    
    frontColor = vec4(mix(vec3(1,0,0), vec3(1,1,1), 1-t),1.0)*N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(finalVertex, 1.0);
}
