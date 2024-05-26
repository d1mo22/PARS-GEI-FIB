#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3  matamb;
in vec3  matdiff;
in vec3  matspec;
in float matshin;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform int car;
uniform vec3 posFocusCar1;
uniform vec3 posFocusCar2;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;
out vec3 fCar1;
out vec3 fCar2;



void main()
{	
    // Passem les dades al fragment shader
    fmatamb  = matamb;

    if (car == 1) fmatdiff = matdiff * vec3(1,0,0);
    else if (car == 2) fmatdiff = matdiff * vec3(0,1,0);
    else fmatdiff = matdiff;

    fmatspec = matspec;
    fmatshin = matshin;

    fvertex = (vec3(View*TG*vec4(vertex,1.0))); // CALCULEU CORRECTAMENT
    fnormal = normalize(inverse(transpose(mat3(View*TG)))*normal); // CALCULEU CORRECTAMENT
    fCar1 = vec3(View * vec4(posFocusCar1, 1.0));
    fCar2 = vec3(View * vec4(posFocusCar2, 1.0));

    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
