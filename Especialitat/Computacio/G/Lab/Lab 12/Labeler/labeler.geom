#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform float size = 0.07;
uniform float depth = -0.01;

void main( void )
{
	//NCD
	vec3 center = vec3(0.0);
	for (int i = 0; i < 3; ++i) {
		vec3 vertexNDC = gl_in[i].gl_Position.xyz / gl_in[i].gl_Position.w;
		center += vertexNDC;
	}
	center /= 3;

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	gfrontColor = vec4(1,1,0,1);

	gl_Position = vec4(center + vec3(-size, -size, depth), 1.0);
	gtexCoord = vec2(0,0);
	EmitVertex();
	gl_Position = vec4(center + vec3(size, -size, depth), 1.0);
	gtexCoord = vec2(7,0);
	EmitVertex();
	gl_Position = vec4(center + vec3(-size, size, depth), 1.0);
	gtexCoord = vec2(0,7);
	EmitVertex();
	gl_Position = vec4(center + vec3(size, size, depth), 1.0);
	gtexCoord = vec2(7,7);
	EmitVertex();

	EndPrimitive();
}
