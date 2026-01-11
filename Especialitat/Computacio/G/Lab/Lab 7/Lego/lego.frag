#version 330 core

const vec3 red = vec3(1, 0, 0);
const vec3 yellow = vec3(1, 1, 0);
const vec3 green = vec3(0, 1, 0);
const vec3 cyan = vec3(0, 1, 1);
const vec3 blue = vec3(0, 0, 1);

in vec3 geomNormal;
in vec3 geomColor;
in vec2 geomTexturePosition;

out vec4 fragColor;

uniform sampler2D sampler;

vec3 legoColor(vec3 color) {
	float r = distance(color, red);
	float y = distance(color, yellow);
	float g = distance(color, green);
	float c = distance(color, cyan);
	float b = distance(color, blue);
	vec3 nearestColor = red;
	float minimumDistance = r;
	
	if (y < minimumDistance) {
		minimumDistance = y;
		nearestColor = yellow;
	}
	
	if (g < minimumDistance) {
		minimumDistance = g;
		nearestColor = green;
	}
	
	if (c < minimumDistance) {
		minimumDistance = c;
		nearestColor = cyan;
	}
	
	if (b < minimumDistance) {
		minimumDistance = b;
		nearestColor = blue;
	}

	return nearestColor;
}

void main() {
	vec3 color = legoColor(geomColor);
	
	if (geomTexturePosition.s >= 0 && geomTexturePosition.t >= 0) {
		color *= texture(sampler, geomTexturePosition).xyz;
	}
	
	fragColor = vec4(color * (geomNormal).z, 1);
}
