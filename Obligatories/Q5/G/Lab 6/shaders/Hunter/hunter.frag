#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

uniform sampler2D jungla;
uniform vec2 viewport;
uniform vec2 mousePosition;
uniform float magnific = 3;

vec4 blurImage( in vec2 coords ) {
    float Pi = 6.28318530718; // Pi*2
    float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
    float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
    float Size = 10.0; // BLUR SIZE (Radius)
   
    vec2 Radius = Size/viewport;

    vec4 Color = texture(jungla, coords);
    for( float d=0.0; d<Pi; d+=Pi/Directions)
    {
        float cd = cos(d);
        float sd = sin(d);
		for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
			Color += texture(jungla, coords+vec2(cd,sd)*Radius*i);		
        }
    }
    
    // Output to screen
    Color /= Quality * Directions - 15.0;
    return  Color;
}

void main()
{
    vec2 pixelCoord = vtexCoord * viewport;

    vec2 p1 = vec2(mousePosition.x + 80, mousePosition.y);
    vec2 p2 = vec2(mousePosition.x - 80, mousePosition.y);

    float zoom = magnific*distance(pixelCoord, mousePosition);
    float distance1 = length(pixelCoord - p1);
    float distance2 = length(pixelCoord - p2);


    if (distance1 < 100 || distance2 < 100) {
        float distF_mouse = distance(pixelCoord, mousePosition) / magnific;
        vec2 direction = normalize(pixelCoord- mousePosition);

        vec2 point2 = mousePosition + direction*distF_mouse;
        point2 = vec2(point2.x/viewport.x, point2.y/viewport.y);

        fragColor = texture(jungla, point2);
    }
    else if (distance1 < 105 || distance2 < 105) fragColor = vec4(0);
    else fragColor = blurImage(vtexCoord);
}
