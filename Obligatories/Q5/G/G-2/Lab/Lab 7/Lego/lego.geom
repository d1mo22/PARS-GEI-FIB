#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 24) out;

in vec3 vertColor[];

out vec3 geomNormal;
out vec3 geomColor;
out vec2 geomTexturePosition;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.2;

vec3 average(vec3 A, vec3 B, vec3 C) {
	return (A + B + C) / 3;
}

vec3 normal(vec3 A, vec3 B, vec3 C) {
	vec3 AB = normalize(B - A);
	vec3 AC = normalize(C - A);
	return normalize(normalMatrix * normalize(cross(AB, AC)));
}

void emitCube(vec3 P, vec3 C, float d) {
	float r = d / 2;
	vec3 xyz = P + vec3(-r, -r, -r);
	vec3 xyZ = P + vec3(-r, -r,  r);
	vec3 xYz = P + vec3(-r,  r, -r);
	vec3 xYZ = P + vec3(-r,  r,  r);
	vec3 Xyz = P + vec3( r, -r, -r);
	vec3 XyZ = P + vec3( r, -r,  r);
	vec3 XYz = P + vec3( r,  r, -r);
	vec3 XYZ = P + vec3( r,  r,  r);
	
	geomColor = C;
	geomTexturePosition = vec2(-1, -1);
	
	geomNormal = normal(xyz, xYz, Xyz).zzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	EndPrimitive();
	
	geomNormal = normal(xyZ, XyZ, xYZ).zzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();

	geomNormal = normal(xyz, xyZ, xYz).zzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	EndPrimitive();
	
	geomNormal = normal(Xyz, XYz, XyZ).zzz;
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();
	
	geomNormal = normal(xyz, Xyz, xyZ).zzz;
	gl_Position = modelViewProjectionMatrix * vec4(xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(Xyz, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(xyZ, 1);
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(XyZ, 1);
	EmitVertex();
	EndPrimitive();
	
	geomNormal = normal(xYz, xYZ, XYz).zzz;
	geomTexturePosition = vec2(0, 0);
	gl_Position = modelViewProjectionMatrix * vec4(xYz, 1);
	EmitVertex();
	geomTexturePosition = vec2(1, 0);
	gl_Position = modelViewProjectionMatrix * vec4(XYz, 1);
	EmitVertex();
	geomTexturePosition = vec2(0, 1);
	gl_Position = modelViewProjectionMatrix * vec4(xYZ, 1);
	EmitVertex();
	geomTexturePosition = vec2(1, 1);
	gl_Position = modelViewProjectionMatrix * vec4(XYZ, 1);
	EmitVertex();
	EndPrimitive();
}

void main(void) {
	//if (gl_PrimitiveIDIn > 0) return;
	vec3 P = average(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz);
	vec3 C = average(vertColor[0], vertColor[1], vertColor[2]);
	emitCube(step * round(P / step), C, step);
}
