#define STB_IMAGE_IMPLEMENTATION 1
#define TINYOBJLOADER_IMPLEMENTATION 1

#include "ConsoleRenderer.h"
#include "Utils.h"
#include "tiny_obj_loader.h"
#include <cassert>
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr
#include <stb_image.h>
#include <vector>




namespace aie
{
    Geometry MakeGeometry(const Vertex* const Verts, GLsizei VertCount, const GLuint* const Indicies, GLsizei IndexCount)
    {

        Geometry NewGeo = {};
        NewGeo.Size = IndexCount;

        glGenVertexArrays(1, &NewGeo.Vao);
        glGenBuffers(1, &NewGeo.Vbo);
        glGenBuffers(1, &NewGeo.Ibo);

        glBindVertexArray(NewGeo.Vao);
        glBindBuffer(GL_ARRAY_BUFFER, NewGeo.Vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewGeo.Ibo);

        glBufferData(GL_ARRAY_BUFFER, VertCount * sizeof(Vertex), Verts, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(GLsizei), Indicies, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UVs));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return NewGeo;
    }

    void FreeGeometry(Geometry& Geo)
    {
        glDeleteBuffers(1, &Geo.Vbo);
        glDeleteBuffers(1, &Geo.Ibo);
        glDeleteVertexArrays(1, &Geo.Vao);

        Geo = {};
    }

    Geometry LoadGeometry(const char* filePath)
    {
        using namespace tinyobj;

        // contains all data for all vertex attributes loaded from the file
        attrib_t vertexAttributes;

        // enumeration of all shapes in obj file
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string error;
        std::string warn;

        bool success = LoadObj(&vertexAttributes, &shapes, &materials, &warn, &error, filePath);

        if (!error.empty())
        {
            fprintf(stderr, "%s", error.c_str());
        }
        if (!success || shapes.size() < 1)
        {
            return {};
        }

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        // Get mesh data
        size_t offSet = 0;
        for (GLsizei i = 0; i < shapes[0].mesh.num_face_vertices.size(); ++i)
        {
            // number of vertices for current face
            GLsizei faceVertices = shapes[0].mesh.num_face_vertices[i];

            assert(faceVertices == 3 && "Faces must be provided in triangles");

            // iterate over vertices used to form current face
            for (unsigned char j = 0; j < faceVertices; ++j)
            {
                tinyobj::index_t idx = shapes[0].mesh.indices[offSet + j];

                tinyobj::real_t vx = vertexAttributes.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = vertexAttributes.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = vertexAttributes.vertices[3 * idx.vertex_index + 2];

                tinyobj::real_t nx = vertexAttributes.normals[3 * idx.normal_index + 0];
                tinyobj::real_t ny = vertexAttributes.normals[3 * idx.normal_index + 1];
                tinyobj::real_t nz = vertexAttributes.normals[3 * idx.normal_index + 2];

                tinyobj::real_t tx = vertexAttributes.texcoords[2 * idx.texcoord_index + 0];
                tinyobj::real_t ty = vertexAttributes.texcoords[2 * idx.texcoord_index + 1];

                vertices.push_back(Vertex{ {vx, vy, vz, 1}, {nx, ny, nz, 1}, {tx, ty} });
                indices.push_back(faceVertices * i + j);
            }
            offSet += faceVertices;
        }

        assert(vertices.size() <= std::numeric_limits<GLsizei>::max());
        assert(indices.size() <= std::numeric_limits<GLsizei>::max());

        return MakeGeometry(&vertices[0], (GLsizei)vertices.size(), &indices[0], (GLsizei)shapes[0].mesh.indices.size());
    }

    Shader LoadShader(const char* VertPath, const char* FragPath)
    {
        std::string VertSource = DumpToString(VertPath);
        std::string FragSource = DumpToString(FragPath);

        return MakeShader(VertSource.c_str(), FragSource.c_str());
    }

    Shader MakeShader(const char* vertSource, const char* fragSource)
    {
        // make the shader object
        Shader newShad = {};
        newShad.Program = glCreateProgram();

        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vert, 1, &vertSource, 0);
        glShaderSource(frag, 1, &fragSource, 0);
        glCompileShader(vert);
        glCompileShader(frag);

        glAttachShader(newShad.Program, vert);
        glAttachShader(newShad.Program, frag);

        glLinkProgram(newShad.Program);

        glDeleteShader(vert);
        glDeleteShader(frag);

        
        return newShad;
    }

    void FreeShader(Shader& shad)
    {
        glDeleteProgram(shad.Program);
        shad = {};
    }

    Texture MakeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
    {
        //Create our return object
        Texture RetVal = {0, width, height, channels };
        
        //Setup the encoding in a way that OpenGL understands
        GLenum OGLFormat = GL_R;
        switch (channels)
        {
        case 1:
            OGLFormat = GL_R; //monochrome
            break;
        case 2:
            OGLFormat = GL_RG; 
            break;
        case 3:
            OGLFormat = GL_RGB; //color or data (specifically directions or offsets)
            break;
        case 4:
            OGLFormat = GL_RGBA; //color or data (that needs a fourth channel)
            break;
        default:
            assert(false && "Unknown channel config");
        }

        //Create a texture object on OpenGL and bind it
        glGenTextures(1, &RetVal.Handle);
        glBindTexture(GL_TEXTURE_2D, RetVal.Handle);

        //Buffer in the texture data
        glTexImage2D(GL_TEXTURE_2D,
            0,
            OGLFormat,
            width,
            height,
            0,
            OGLFormat,
            GL_UNSIGNED_BYTE,
            pixels);

        //Describe the data
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        //Return
        return RetVal;
    }

    Texture LoadTexture(const char* ImagePath)
    {
        //Create some variable to be filled in by stb
        int ImageWidth = 0;
        int ImageHeight = 0;
        int ImageFormat = 0;

        unsigned char* RawPixelData = nullptr;

        //Create our return value
        Texture RetVal = {};

        //Load the texture
        stbi_set_flip_vertically_on_load(true);

        RawPixelData = stbi_load(ImagePath,
            &ImageWidth,
            &ImageHeight,
            &ImageFormat,
            STBI_default);

        assert(RawPixelData != nullptr && "Failed to load image!");

        RetVal = MakeTexture(ImageWidth, ImageHeight, ImageFormat, RawPixelData);

        stbi_image_free(RawPixelData);

        //Return the texture
        return RetVal;
    }

    void FreeTexture(Texture& Tex)
    {
        glDeleteTextures(1, &Tex.Handle);
        // Zero out to prevent accidental reuse
        Tex = {};
    }

    void Draw(const Shader& shad, const Geometry& geo)
    {
        //assert(Shad.Program != 0);
        //assert(Geo.Vao != 0);

        glUseProgram(shad.Program);
        glBindVertexArray(geo.Vao);

        glDrawElements(GL_TRIANGLES, geo.Size, GL_UNSIGNED_INT, 0);
    }

    void SetUniform(const Shader& shad, GLuint location, const glm::mat4& value)
    {
        glProgramUniformMatrix4fv(shad.Program, location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void SetUniform(const Shader& shad, GLuint location, float value)
    {
        glProgramUniform1fv(shad.Program, location, 1, &value);
    }

    void SetUniform(const Shader& shad, GLuint location, const Texture& tex, int textureSlot)
    {
        //Specify the texture slot you want to activate
        glActiveTexture(GL_TEXTURE0 + textureSlot);

        //Bind the texture to that slot
        glBindTexture(GL_TEXTURE_2D, tex.Handle);

        //Specify that texture slot as the value for the uniform
        glProgramUniform1i(shad.Program, location, textureSlot);
    }
}