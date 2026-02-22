#ifndef GLH_H
#define GLH_H





#include "GLFW/glfw3.h"
#include "glad/glad.h"







/* structs */


typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int vertexCount;
    int indexCount;
} GLH_Mesh;



    
/* functions defination */


unsigned int GLH_CompileShader(const char** shaderSrc, int TotalShader, int type);


void GLH_SetupVAO(unsigned int *VAO, int total);
void GLH_SetBufferData(GLenum type, unsigned int *obj, void* data, size_t size, int total, GLenum usage);

unsigned int GLH_CreateProgram(unsigned int VertexShader, unsigned int FragmentShader);

void GLH_SetVertexAttrib(
    unsigned int index, 
    int size, 
    GLenum type,
    GLboolean normalized, 
    int stride, 
    void* offset
);


void GLH_SetupTex2D(unsigned int *tex, int total);



#ifdef GLH_IMPLEMENTATION


/* functions compelete defination */


unsigned int GLH_CompileShader(const char** shaderSrc, int TotalShader, int type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, TotalShader, shaderSrc, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader compilation failed: %s\n", infoLog);   // or printf, whatever you use
        // optionally: exit(-1); or set global error flag
    }

    return shader;
}





void GLH_SetBufferData(GLenum type, unsigned int *obj, void* data, size_t size, int total, GLenum usage)
{
    glGenBuffers(total, obj);
    glBindBuffer(type, *obj);
    glBufferData(type, size, data, usage);
}




unsigned int GLH_CreateProgram(unsigned int VertexShader, unsigned int FragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, VertexShader);
    glAttachShader(program, FragmentShader);
    int success;
    char infoLog[512];

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Program linking failed: %s\n", infoLog);
    }

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    

    return program;
}





void GLH_SetupVAO(unsigned int *VAO, int total)
{
    glGenVertexArrays(total, VAO);
    glBindVertexArray(*VAO);
}




void GLH_SetVertexAttrib(unsigned int index, int size, GLenum type, GLboolean normalized, int stride, void* offset)
{
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}




void GLH_SetupTex2D(unsigned int *tex, int total)
{
    glGenTextures(total, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
}










#endif




/* macros */


#define GLH_WND_DATA(width, height, title)\
    (width), (height), (title), NULL, NULL




#define GLH_UseGL330Version()\
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#define GLH_GL_Load()\
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)


#define GLH_ClearColor(r, g, b)\
    glClearColor(r, g, b, 1.0f);\
    glClear(GL_COLOR_BUFFER_BIT);



#define GLH_SetupTex(tex, total)\
    GLH_SetupTex2D(tex, total);



#define GLH_SetBufferDataSimple(type, obj, vertices, size, total)\
    GLH_SetBufferData(type, obj, vertices, size, total, GL_STATIC_DRAW)



#define GLH_SetBufferDataFast(type, obj, vertices, size, total)\
    GLH_SetBufferData(type, obj, vertices, size, total, GL_DYNAMIC_DRAW)



#define GLH_DrawTriArrays(index, TotalVertices)\
    glDrawArrays(GL_TRIANGLES, index, TotalVertices)



#define GLH_BindVAO(VAO)\
    glBindVertexArray(VAO)


#define GLH_BindTex2D(tex)\
    glBindTexture(GL_TEXTURE_2D, tex)




#define GLH_BindTex(tex)\
    glBindTexture(GL_TEXTURE_2D, tex)

 


#define GLH_DrawTriElms(IndicesNum, type, offset)\
    glDrawElements(GL_TRIANGLES, IndicesNum, type, offset)



#define GLH_SetTex2Dparami(pname, param)    glTexParameteri(GL_TEXTURE_2D, pname, param)
#define GLH_SetTex2Dparamf(pname, param)    glTexParameterf(GL_TEXTURE_2D, pname, param)
#define GLH_SetTexparami(pname, param)  glTexParameteri(GL_TEXTURE_2D, pname, param)
#define GLH_SetTexparamf(pname, param)  glTexParameterf(GL_TEXTURE_2D, pname, param)




#define GLH_SetColorFormat(channels)    (channels == 4) ? GL_RGBA : GL_RGB;


#define GLH_GenMipmap(type)     glGenerateMipmap(type);


#define GLH_DelVAO(VAO, total)\
    glDeleteVertexArrays(total, VAO)



#define GLH_DelBuffers(buffers, total)\
    glDeleteBuffers(total, buffers)




#define GLH_DelProgram(program)\
    glDeleteProgram(program)






/*  flags & const & macros  */

#define GLH_VBO     (GL_ARRAY_BUFFER)
#define GLH_EBO     (GL_ELEMENT_ARRAY_BUFFER)


#define GLH_FLOAT       (GL_FLOAT)
#define GLH_UINT        (GL_UNSIGNED_INT)
#define GLH_UBYTE       (GL_UNSIGNED_BYTE)


// textures

#define GLH_TEX2D       (GL_TEXTURE_2D)
#define GLH_TEX         (GLH_TEX2D)

#endif