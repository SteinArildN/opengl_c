#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glmath.h"
#include "gldata.h"

#include "glfunc.h"

//compiles a shader program from a vertex and shader shaders
GLuint OPENGLcompile_shader(const char* vert, const char* frag);

//setup buffer for rendering cubes
//this one is simple. meaning that it only generates an array of vertices
//so use draw array!
void OPENGLsetup_buffers_simple(glSimpleBuffers* buffers, glSimpleBufferContent* content, int is_textured);

//setup buffer for rendering cubes
//this one sets up a buffer for vertices, and indices
//so use draw element!
void OPENGLsetup_buffers(glBuffers* buffers, glBufferContent* content, int is_textured);

//binds a uniform to a shaderprogram
//this function is for passing 4x4 matricies, and only matricies.... damn you c!!
void OPENGLbindUniform_Mat4f(GLuint program, const char* field, mat4f data);

//this loads textures through stb_image (unit 0)
//should probably revisit this
GLuint OPENGLloadTexture(const char* filename);