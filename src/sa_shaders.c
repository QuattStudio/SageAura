/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/









// sa_shaders.c (replace contents)
#include "sa_shaders.h"

const char* SA_VertexShaderSrc_I =
"#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"\n"
"out vec4 vertexColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 uProjection;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = uProjection * vec4(aPos, 0.0, 1.0);\n"
"    vertexColor = aColor;\n"
"    TexCoord = aTexCoord;\n"
"}\n";

const char* SA_FragmentShaderSrc_I =
"#version 330 core\n"
"in vec4 vertexColor;\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D uTexture;\n"
"\n"
"void main()\n"
"{\n"
"    vec4 tex = texture(uTexture, TexCoord);\n"
"    FragColor = tex * vertexColor; // multiply texture by vertex color (tint)\n}\n";