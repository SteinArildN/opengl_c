#pragma once
#include "GLFW/glfw3.h"

//structs holding gl related data
//these are passed into functions
typedef struct {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} glBuffers;

typedef struct {
	GLuint VAO;
	GLuint VBO;
} glSimpleBuffers;

typedef struct {
	float* vertices;
	unsigned int* indices;
	size_t vertices_size;
	size_t indices_size;
} glBufferContent;

typedef struct {
	float* vertices;
	size_t vertices_size;
} glSimpleBufferContent;

//GL DATA
// Cube vertex data with unique colors for each face
extern float vertices[];
// Cube indices for drawing with EBO (adjusted for new vertices)
extern unsigned int indices[];

extern float vertices_tex[];

// Indices to define the cube's faces using two triangles per face
extern unsigned int indices_tex[];

extern float vertices_simple[];
extern size_t vertices_simple_size;
extern float vertices_simple_face[];
extern size_t vertices_simple_face_size;

// Vertex Shader Source
extern const char* vertexShaderSource;

// Fragment Shader Source
extern const char* fragmentShaderSource;

// Vertex Shader Source with texture!!
extern const char* vertexTextureShaderSource;

// Fragment Shader Source
extern const char* fragmentTextureShaderSource;