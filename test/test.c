// #include <stdio.h>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <math.h>


// #define GLH_IMPLEMENTATION
// #include "glh.h"


// const char* vertSrc =
// "#version 330 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "void main() {\n"
// "    gl_Position = vec4(aPos, 1.0);\n"
// "}\n";

// const char* fragSrc =
// "#version 330 core\n"
// "out vec4 FragColor;\n"
// "uniform vec4 uColor;\n"
// "void main() {\n"
// "    FragColor = uColor;\n"
// "}\n";

// int main(void)
// {
//     glfwInit();
//     GLH_UseGL330Version();


//     GLFWwindow* window = glfwCreateWindow(GLH_WND_DATA(800, 600, "Rect"));
//     glfwMakeContextCurrent(window);
    
//     GLH_GL_Load();


//     float vertices[] = {
//          0.5f,  0.5f, 0.0f,
//          0.5f, -0.5f, 0.0f,
//         -0.5f, -0.5f, 0.0f,
//         -0.5f,  0.5f, 0.0f
//     };

//     unsigned int indices[] = {
//         0, 1, 3,
//         1, 2, 3
//     };


//     unsigned int VAO, VBO, EBO;

//     GLH_GenAndBindVAO(&VAO, 1);

    
//     GLH_SetBufferDataSimple(GLH_VBO, &VBO, vertices, sizeof(vertices), 1);
//     GLH_SetBufferDataSimple(GLH_EBO, &EBO, indices,  sizeof(indices),  1);


//     GLH_SetVertexAttrib(0, 3, GLH_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);


//     /* compile shaders */

//     unsigned int vs = GLH_CompileShader(&vertSrc, 1, GL_VERTEX_SHADER);
//     unsigned int fs = GLH_CompileShader(&fragSrc, 1, GL_FRAGMENT_SHADER);


//     unsigned int program = GLH_CreateProgram(vs, fs);


//     /* get uniform location once before loop */
//     int colorLoc = glGetUniformLocation(program, "uColor");

//     while (!glfwWindowShouldClose(window)) {
//         GLH_ClearColor(0.1f, 0.1f, 0.15f);


//         glUseProgram(program);

//         /* change color based on time */
//         float time = (float)glfwGetTime();
//         float r = (sin(time * 1.0f) + 1.0f) / 2.0f;
//         float g = (sin(time * 2.0f) + 1.0f) / 2.0f;
//         float b = (sin(time * 3.0f) + 1.0f) / 2.0f;
//         glUniform4f(colorLoc, r, g, b, 1.0f);

//         GLH_BindVAO(VAO);

//         GLH_DrawTriElms(6, GLH_UINT, 0);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     GLH_DelVAO(&VAO, 1);
//     GLH_DelBuffers(&VBO, 1);
//     GLH_DelBuffers(&EBO, 1);

//     GLH_DelProgram(program);


//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }

































#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLH_IMPLEMENTATION
#include "glh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const char* vertSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aUV;\n"
"out vec2 UV;\n"
"void main(){\n"
"   UV = aUV;\n"
"   gl_Position = vec4(aPos,1.0);\n"
"}\n";

const char* fragSrc =
"#version 330 core\n"
"in vec2 UV;\n"
"out vec4 FragColor;\n"
"uniform sampler2D tex;\n"
"void main(){\n"
"   FragColor = texture(tex, UV);\n"
"}\n";


int main(void)
{
    glfwInit();
    GLH_UseGL330Version();

    GLFWwindow* window = glfwCreateWindow(GLH_WND_DATA(800,600,"Image"));

    glfwMakeContextCurrent(window);
    GLH_GL_Load();


    // rectangle + UV
    float vertices[] = {
        // pos        // UV
         0.5f,  0.5f, 0,   1,1,
         0.5f, -0.5f, 0,   1,0,
        -0.5f, -0.5f, 0,   0,0,
        -0.5f,  0.5f, 0,   0,1
    };

    unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };

    unsigned int VAO,VBO,EBO;

    GLH_SetupVAO(&VAO, 1);

    GLH_SetBufferDataSimple(GLH_VBO, &VBO, vertices, sizeof(vertices), 1);
    GLH_SetBufferDataSimple(GLH_EBO, &EBO, indices, sizeof(indices), 1);


    // position
    GLH_SetVertexAttrib(0, 3, GLH_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);

    // UV
    GLH_SetVertexAttrib(1, 2, GLH_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));


    // shaders
    unsigned int vs = GLH_CompileShader(&vertSrc, 1, GL_VERTEX_SHADER);
    unsigned int fs = GLH_CompileShader(&fragSrc, 1, GL_FRAGMENT_SHADER);

    unsigned int program = GLH_CreateProgram(vs, fs);


    // 🔥 LOAD IMAGE
    int w, h, channels;
    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load("spec.PNG", &w, &h, &channels, 0);

    if(!data){
        printf("image failed\n");
        return -1;
    }

    unsigned int tex;
    GLH_SetupTex(&tex, 1);


    GLH_SetTexparami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLH_SetTexparami(GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLH_SetTexparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLH_SetTexparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    GLenum format = GLH_SetColorFormat(channels);

    glTexImage2D(GLH_TEX, 0, format, w, h, 0, format, GLH_UBYTE, data);
    GLH_GenMipmap(GLH_TEX);


    stbi_image_free(data);


    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "tex"), 0);


    while(!glfwWindowShouldClose(window))
    {
        GLH_ClearColor(0.1f, 0.1f, 0.15f);

        glUseProgram(program);

        GLH_BindTex(tex);

        GLH_BindVAO(VAO);
        GLH_DrawTriElms(6, GLH_UINT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    GLH_DelVAO(VAO, 1);
    GLH_DelBuffers(VBO, 1);
    GLH_DelBuffers(EBO, 1);

    GLH_DelProgram(program);
    

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
