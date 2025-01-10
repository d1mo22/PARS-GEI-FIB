#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform vec3 boundingBoxMax, boundingBoxMin;
uniform mat4 modelViewProjectionMatrix;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void drawSquareY() {
	gfrontColor = vec4(0,1,0,1); 
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z, 1);
    EmitVertex();
    
    EndPrimitive();
}

void drawSquareX(bool left) {
	gfrontColor = vec4(1,0,0,1);
	if (left) {
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z, 1);
		EmitVertex();
	}
	else {
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z, 1);
		EmitVertex();
		
		gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z, 1);
		EmitVertex();
	}
	EndPrimitive();
}

void drawSquareZ() {
	gfrontColor = vec4(0,0,1,1);

    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * vec4(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z, 1);
    EmitVertex();
    
    EndPrimitive();	
}

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
		
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn == 0) {
		drawSquareY();
		drawSquareX(true);
		drawSquareX(false);
		drawSquareZ();
	}
}
