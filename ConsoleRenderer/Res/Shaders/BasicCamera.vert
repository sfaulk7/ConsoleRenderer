#version 430 core

//Vertex Attributes
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 normal;

//Uniforms
layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

out vec2 vertUV;
out vec3 vertNormal;
out vec4 vertPos;

void main()
{
    //EXPORTS to FRAGMENT SHADER
    vertPos = position;
    vertNormal = mat3(transpose(inverse(model))) * normal.xyz;
    vertUV = uv;
    //vertUV.x += sin(time);

    //VERTEX SHADER LOGIC POSITION
    //vec4 myPosition = position;
    //myPosition.y += sin(time) + displacement;

    //transform object from ...
    // - OBJECT to WORLD (model)
    // - WORLD to CAMERA (view)
    // - CAMERA to CLIP (proj)
    gl_Position = proj * view * model * position;
}