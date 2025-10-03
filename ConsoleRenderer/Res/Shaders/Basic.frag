#version 430 core

out vec4 vertColor;

layout (location = 3) uniform float time;

void main()
{
    //vertColor = vec4(0, 0, 1, 1); //Blue
    vertColor = vec4(sin(time), sin(time+1), sin(time+2), 1.0); //Rainbow over time
}

//const char * basicFrag =
//        "#version 430 core\n"
//        "out vec4 vertColor;\n"
//        "in vec4 vectorColors;\n"
//        "void main() { vertColor = vectorColors; }";