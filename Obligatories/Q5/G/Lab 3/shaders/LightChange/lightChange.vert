//Does not work

#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexCoord;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec4 eyePosition = modelViewMatrix * vec4(vertexPosition, 1.0);
    fragPosition = eyePosition.xyz;
    fragNormal = normalize(normalMatrix * vertexNormal);
    fragTexCoord = fract(vertexTexCoord);

    gl_Position = projectionMatrix * eyePosition;
}
