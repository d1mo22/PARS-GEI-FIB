#version 330 core

in vec4 frontColor;
in vec2 st;
out vec4 fragColor;

uniform sampler2D invaders;

void drawDefender() {
    vec2 tex = vec2(3/4. + fract(st.s)/4, fract(st.t)/4);
    fragColor = texture(invaders, tex);
}

void drawPlayer() {
    vec2 tex = vec2(3/4. + fract(st.s)/4,1/4.+ fract(st.t)/4);
    fragColor = texture(invaders, tex);
}

void drawShip(float s, float t) {
    vec2 tex = vec2(s/4. + fract(st.s)/4, t/4. + fract(st.t)/4);
    fragColor = texture(invaders, tex);

}

void main()
{
    if (st.t < 1 || st.t > 14 || (st.t > 2 && st.t < 3 && !(st.s > 2 && st.s < 3 || st.s > 5 && st.s < 6 || st.s > 8 && st.s < 9 || st.s > 12 && st.s < 13))) {
        fragColor = vec4(0);
    } else if (st.t < 2 && st.t > 1 && st.s > 7 && st.s < 8) {
        drawPlayer();
    } else if (st.t < 3 && st.t > 2) {
        drawDefender();
    } else {
        int row = int(st.t) - 4;
        int col = int(st.s) - 1;
        if (row >= 0 && row < 9 && col >= 0 && col < 13) {
            drawShip(float(row / 4), float(row % 4));
        } else {
            fragColor = vec4(0);
        }
    }
}
