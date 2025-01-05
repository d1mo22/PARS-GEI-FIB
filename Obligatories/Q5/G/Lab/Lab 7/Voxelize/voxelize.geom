#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 24) out;

out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.2;

vec3 triangleCentroid(vec3 A, vec3 B, vec3 C) {
	return (A + B + C) / 3;
}

vec3 normal(vec3 A, vec3 B, vec3 C) {
	vec3 AB = normalize(B - A);
	vec3 AC = normalize(C - A);
	return normalize(normalMatrix * normalize(cross(AB, AC)));
}

void emitCube(vec3 C, float d) {
	float r = d / 2;
	vec3 xyz = C + vec3(-r, -r, -r);
	vec3 xyZ = C + vec3(-r, -r,  r);
	vec3 xYz = C + vec3(-r,  r, -r);
	vec3 xYZ = C + vec3(-r,  r,  r);
	vec3 Xyz = C + vec3( r, -r, -r);
	vec3 XyZ = C + vec3( r, -r,  r);
	vec3 XYz = C + vec3( r,  r, -r);
	vec3 XYZ = C + vec3( r,  r,  r);
	
	gfrontColor = normal(xyz, xYz, Xyz).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	EndPrimitive();
	
	gfrontColor = normal(xyZ, XyZ, xYZ).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();
	
	gfrontColor = normal(xyz, xyZ, xYz).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	EndPrimitive();
	
	gfrontColor = normal(Xyz, XYz, XyZ).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();
	
	gfrontColor = normal(xyz, Xyz, xyZ).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	EndPrimitive();
	
	gfrontColor = normal(xYz, xYZ, XYz).zzzz;
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();
}

void main(void) {
	//if (gl_PrimitiveIDIn > 0) return;
	vec3 C = triangleCentroid(
		gl_in[0].gl_Position.xyz,
		gl_in[1].gl_Position.xyz,
		gl_in[2].gl_Position.xyz);
	emitCube(step * round(C / step), step);
}

