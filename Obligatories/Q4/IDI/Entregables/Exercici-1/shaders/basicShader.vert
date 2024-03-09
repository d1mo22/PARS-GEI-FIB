#version 330 core

in vec3 vertex;
in vec3 color;
out vec3 fcolor;
uniform mat4 TG;

void main()  {
    gl_Position = TG * vec4 (vertex, 1.0);
    fcolor = color;
}
