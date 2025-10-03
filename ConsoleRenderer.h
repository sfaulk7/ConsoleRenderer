#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace aie
{

    struct Vertex
    {
        glm::vec4 Pos;
        glm::vec4 Normals;
        glm::vec2 UVs;
        //glm::vec4 Color;
    };

    struct Geometry
    {
        GLuint Vao = 0, Vbo = 0, Ibo = 0;
        GLuint Size = 0;
    };

    struct Shader
    {
        GLuint Program;
    };

    struct Texture
    {
        GLuint Handle; //OpenGl texture name
        unsigned Width, Height, Channels;
    };

    Geometry MakeGeometry(const Vertex* const Verts, GLsizei VertCount, const GLuint* const Indicies, GLsizei IndexCount);
    void FreeGeometry(Geometry& Geo);
    Geometry LoadGeometry(const char* filePath);
    
    Shader LoadShader(const char* VertPath, const char* FragPath);
    Shader MakeShader(const char* vertSource, const char* fragsource);
    void FreeShader(Shader& shad);

    Texture MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
    Texture LoadTexture(const char* ImagePath);
    void FreeTexture(Texture& Tex);

    void Draw(const Shader& shad, const Geometry& geo);

    void SetUniform(const Shader& shad, GLuint location, const glm::mat4& value);
    void SetUniform(const Shader& shad, GLuint location, float value);
    void SetUniform(const Shader& shad, GLuint location, const Texture& tex, int textureSlot);
    void SetUniform(const Shader& shad, GLuint location, const glm::vec3& value);

}