#version 430 core

//Vertex Attributes
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 uv;

//Uniforms
layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

out vec2 vertUV;
out vec3 vertNormal;
out vec4 vertPos;

void main()
{
    //VERTEX SHADER LOGIC POSITION
    vertPos = position;

    //transform object from ...
    // - OBJECT to WORLD (model)
    // - WORLD to CAMERA (view)
    // - CAMERA to CLIP (proj)
    gl_Position = proj * view * model * position;

    //EXPORTS to FRAGMENT
    vertUV = uv;
    vertUV.x += sin(time);
    
    vertNormal = mat3(transpose(inverse(model))) * normal.xyz;
}