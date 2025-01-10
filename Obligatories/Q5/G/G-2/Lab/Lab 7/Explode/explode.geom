#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform float time;
uniform float speed = 0.5;

in vec4 vfrontColor[];
in vec3 N[];
out vec4 gfrontColor;

vec3 explosion(vec3 P, vec3 direction) {
	return P + speed * time * direction;
}

void main( void )
{
	vec3 direction = (N[0] + N[1] + N[2])/3;
	for (int i = 0 ; i < 3 ; i++) {
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * vec4(explosion(gl_in[i].gl_Position.xyz, direction), 1.0);
		EmitVertex();
	}
    EndPrimitive();
}
