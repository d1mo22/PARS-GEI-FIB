#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 st;

uniform sampler2D colormap;

void pintarCantonades(int offset) {
	vec2 tex;	
	
	// Canonada inferior esquerra 
	if (st.s < 1 && st.t < 1) tex = vec2(5./6. - fract(st.s)/6, 1 - fract(st.t));
	// Canonada superior esquerra
	else if (st.s < 1 && st.t > 14) tex = vec2(5./6. - fract(st.s)/6, fract(st.t));
	// Canonada inferior dreta
	else if (st.s > 14 && st.t < 1) tex = vec2(5./6. - fract(st.t)/6, fract(st.s));
	// Canonada superior dreta
	else if (st.s > 14 && st.t > 14) tex = vec2(2./3. + fract(st.s)/6, fract(st.t));
	// Canonada vertical
	else if (st.s < 1 || st.s > 14 || offset == 1) tex = vec2(0.5 + fract(st.t)/6, fract(st.s));
	// Canonada horitzontal
	else if (st.t < 1 || st.t > 14) tex = vec2(0.5 + fract(st.s)/6, fract(st.t));
	// Pintem la canonada
	fragColor = texture(colormap, tex);
}

void pintarFantasma(int b) {
	vec2 tex;
	if (b == 0) tex = vec2(fract(st.s)/6, fract(st.t));
	else if (b == 1) tex = vec2(fract(st.t)/6, 1 - fract(st.s));
	fragColor = texture(colormap, tex);
}

void pintarPacman() {
	vec2 tex = vec2(1./6. + fract(st.s)/6, fract(st.t));
	fragColor = texture(colormap, tex);
}

void pintarPildora() {
	vec2 tex = vec2(5./6. + fract(st.s)/6, fract(st.t));
	fragColor = texture(colormap, tex);
}

void main() {
	if (st.s < 1 || st.s > 14 || st.t < 1 || st.t > 14) pintarCantonades(0);
	else if (st.s < 6 && st.s > 5 && st.t > 1 && st.t < 2) pintarFantasma(0);
	else if (st.s < 8 && st.s > 7 && st.t > 3 && st.t < 4) pintarFantasma(1);
	else if (st.s < 5 && st.s > 4 && st.t > 1 && st.t < 2) pintarPacman();
	else if ((int(st.s) % 2) != 0 || (st.t < 8 && st.t > 7) || (st.t > 13 && st.t < 14) || (st.t > 1 && st.t < 2)) pintarPildora();
    else pintarCantonades(1);
}