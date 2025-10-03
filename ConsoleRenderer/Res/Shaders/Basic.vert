#version 430 core

layout (location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}

//const char* basicVert =
//        "#version 430 core\n"
//        "layout (location = 0) in vec4 position;\n"
//        "layout (location = 1) in vec4 colors;\n"
//        "out vec4 vectorColors;\n"
//        "void main() {vectorColors = colors; gl_Position = position; }";