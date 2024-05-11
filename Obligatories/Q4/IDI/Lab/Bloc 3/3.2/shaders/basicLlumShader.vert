#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem del focus de llum

out vec3 fmatamb;
out vec3 fmatdiff;
out vec3 fmatspec;
out float fmatshin;

out vec3 fVertexSCO;
out vec3 fNormalSCO;
out vec3 fposFSCO;

uniform vec3 posFocus;

//Vertice y normal sse pasan en SCO

void main()
{	
    fmatamb = matamb; 
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);

    mat4 SCO = view*TG;

    mat3 NormalMatrix = inverse(transpose(mat3(SCO)));
    vec3 normalSCO = NormalMatrix*normal;
    fNormalSCO = normalize(normalSCO);

    fVertexSCO = (SCO*vec4(vertex, 1.0)).xyz;

    fposFSCO = (view * vec4(posFocus,1.0)).xyz;
    //vec3 posFSCO = posFocus;

    //vec3 L = posFSCO - vertexSCO;
    //L = normalize(L); //Normalitzat

    //fcolor = ambient+difus+especular;
 
}
