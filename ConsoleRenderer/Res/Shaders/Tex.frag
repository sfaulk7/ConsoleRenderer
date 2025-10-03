#version 430 core

layout (location = 3) uniform sampler2D albedo;
layout (location = 4) uniform vec3 ambientLightColor;
layout (location = 5) uniform vec3 lightDir;
layout (location = 6) uniform vec3 lightColor;
layout (location = 7) uniform vec3 lightDir2;
layout (location = 8) uniform vec3 lightColor2;

in vec4 vertPos;
in vec2 vertUV;
in vec3 vertNormal;

out vec4 fragColor;

void main()
{
    float d = max(0, dot(vertNormal, -lightDir));
    vec3 diffuse = d * lightColor;
    vec4 baseColor = texture(albedo, vertUV);

    float d2 = max(0, dot(vertNormal, -lightDir2));
    vec3 diffuse2 = d2 * lightColor2;

    fragColor.xyz = baseColor.xyz * (ambientLightColor + diffuse + diffuse2);
    fragColor.a = baseColor.a;

    //fragColor = texture(albedo, vertUV);
};