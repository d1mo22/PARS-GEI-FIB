#version 330 core

in vec4 frontColor;
in vec2 st;
out vec4 fragColor;
/* V1
void main()
{
    vec4 color;

    if (st.t > 2.0 / 3.0) {
        color = vec4(0.0, 1.0, 0.0, 1.0); // Verde
    } else if (st.t > 1.0 / 3.0) {
        color = vec4(1.0, 1.0, 0.0, 1.0); // Amarillo
    } else {
        color = vec4(0.0, 0.0, 1.0, 1.0); // Azul
    }
    fragColor = color;
}
*/

/* V2
void main()
{
    vec4 color;
    vec2 stp = st * vec2(4/3., 1);
    vec2 centre = vec2(0.5)*vec2(4/3., 1);

    if (distance(stp, centre) < 0.2) color = vec4(0,1,0,1);
    else if (st.s > 2.0 / 3.0) {
        color = vec4(1.0, 1.0, 0.0, 1.0); // Verde
    } else if (st.s > 1.0 / 3.0) {
        color = vec4(0.0, 0.0, 1.0, 1.0); // Amarillo
    } else {
        color = vec4(1.0, 0.0, 0.0, 1.0); // Azul
    }
    fragColor = color;
}
*/

void main()
{
    vec4 color;
    vec2 stp = st * vec2(4/3., 1);
    vec2 centre = vec2(0.3, 0.5)*vec2(4/3., 1);
    vec2 centreLluna = vec2(0.7, 0.5)*vec2(4/3., 1);
    vec2 centreLluna2 = vec2(0.55, 0.5)*vec2(4/3., 1);

    if (distance(stp, centre) < 0.2 || distance(stp, centreLluna) < 0.3 && distance(stp, centreLluna2) > 0.3) color = vec4(1);
    else color = vec4(0.0, 0.0, 1.0, 1.0); // Blau

    fragColor = color;
}
