#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin, boundingBoxMax;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

	gfrontColor = vec4(0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 P = gl_in[i].gl_Position;
		P.y = boundingBoxMin.y;
		//P.xz *= 1.5;
		gl_Position = modelViewProjectionMatrix * P;
		EmitVertex();
	}
    EndPrimitive();

	gfrontColor = vec4(0,1,1,1);
	if (gl_PrimitiveIDIn == 0) {
		vec3 C = vec3((boundingBoxMax+boundingBoxMin)/2);
		float R = distance(boundingBoxMax, boundingBoxMin)/2;
		float y = boundingBoxMin.y - 0.01;
		gl_Position = modelViewProjectionMatrix * vec4(C.x+R, y, C.z-R,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x-R, y, C.z-R,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x+R, y, C.z+R,1.0); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(C.x-R, y, C.z+R,1.0); EmitVertex();
	}
	EndPrimitive();
}
