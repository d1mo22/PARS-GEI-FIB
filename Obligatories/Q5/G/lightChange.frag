#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 fragColor;

uniform float time;
uniform sampler2D textureSampler;
uniform vec3 lightPosition;
uniform vec3 matSpecular;
uniform vec3 lightSpecular;
uniform float matShininess;

vec3 calculateDiffuseLight(float t) {
    float cycleTime = mod(t, 2.0);
    if (cycleTime < 1.0) {
        return vec3(0.8) * cycleTime;
    } else {
        return vec3(0.8) * (2.0 - cycleTime);
    }
}

vec3 getMaterialDiffuse(float t, vec2 texCoord) {
    int imageIndex = int(mod(t / 2.0, 12.0)) + 1;
    int row = (imageIndex - 1) / 3;
    int col = (imageIndex - 1) % 3;
    vec2 subImageCoord = texCoord / 3.0 + vec2(col, row) / 3.0;
    return texture(textureSampler, subImageCoord).rgb;
}

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(-fragPosition);
    vec3 L = normalize(lightPosition - fragPosition);
    vec3 R = reflect(-L, N);

    float t = mod(time, 6.0);
    vec3 lightDiffuse = calculateDiffuseLight(t);
    vec3 matDiffuse = getMaterialDiffuse(t, fragTexCoord);

    float NdotL = max(dot(N, L), 0.0);
    vec3 diffuse = lightDiffuse * matDiffuse * NdotL;

    float RdotV = max(dot(R, V), 0.0);
    vec3 specular = vec3(0.0);
    if (NdotL > 0.0) {
        specular = lightSpecular * matSpecular * pow(RdotV, matShininess);
    }

    fragColor = vec4(diffuse + specular, 1.0);
}
