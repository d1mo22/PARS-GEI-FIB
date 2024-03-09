#version 330 core

out vec4 FragColor;

uniform int indiceColor;
in vec3 fcolor; 

void main() {
    //FragColor = vec4(0.20, 0.60, 0.10, 1);
    FragColor = vec4(fcolor, 1);
}
