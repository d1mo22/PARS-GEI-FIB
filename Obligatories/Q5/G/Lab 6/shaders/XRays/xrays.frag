#version 330 core

in vec2 st;
out vec4 fragColor;

uniform sampler2D foot0;
uniform sampler2D foot1;
uniform sampler2D foot2;
uniform sampler2D foot3;

const float R = 80.0;

uniform int layer = 1;

uniform vec2 mousePosition;
uniform bool virtualMouse = false;
uniform float mouseX, mouseY; 

vec2 mouse()
{
	if (virtualMouse) return vec2(mouseX, mouseY);
	else return mousePosition;
}

void main()
{
	// a completar. Recorda usar mouse() per obtenir les coords del mouse, en window space
	//float d = distance(vec2(gl_FragCoord.x/gl_FragCoord.w, gl_FragCoord.y/gl_FragCoord.w), mouse());
	vec4 foot = texture(foot0, st);
	vec4 xray;
	float d = distance(gl_FragCoord.xy, mouse());
	if (d >= R) fragColor = foot;
	else {
		switch (layer) {
			case 1:
				xray = texture(foot1, st);
				fragColor = mix(xray, foot, d/R);
				break;
			case 2:
				xray = texture(foot2, st);
				fragColor = mix(xray, foot, d/R);
				break;
			case 3:
				xray = texture(foot3, st);
				fragColor = mix(xray, foot, d/R);
				break;
			default:
				fragColor = texture(foot0, st);
		}
	}
	

}
