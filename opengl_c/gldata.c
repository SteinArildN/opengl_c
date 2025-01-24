#pragma once
#include "gldata.h"

//GL DATA
// Cube vertex data with unique colors for each face
float vertices[] = {
	// Positions           // Colors (one color per face)
	// Back face (Red)
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

	// Front face (Green)
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

	// Left face (Blue)
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

	// Right face (Yellow)
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

	 // Top face (Magenta)
	 -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
	  0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

	 // Bottom face (Cyan)
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f
};

// Cube indices for drawing with EBO (adjusted for new vertices)
unsigned int indices[] = {
	0, 1, 2, 2, 3, 0,       // Back face
	4, 5, 6, 6, 7, 4,       // Front face
	8, 9, 10, 10, 11, 8,    // Left face
	12, 13, 14, 14, 15, 12, // Right face
	16, 17, 18, 18, 19, 16, // Top face
	20, 21, 22, 22, 23, 20  // Bottom face
};

float vertices_tex[] = {
	// Positions         // Colors            // Texture Coordinates
	// Front face
	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Bottom-right
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Top-left
	// Back face
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Bottom-right
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f   // Top-left
};

// Indices to define the cube's faces using two triangles per face
unsigned int indices_tex[] = {
	// Front face
	0, 1, 2,  0, 2, 3,
	// Back face
	4, 5, 6,  4, 6, 7,
	// Left face
	4, 0, 3,  4, 3, 7,
	// Right face
	1, 5, 6,  1, 6, 2,
	// Bottom face
	4, 5, 1,  4, 1, 0,
	// Top face
	3, 2, 6,  3, 6, 7
};

float vertices_simple[] = {
	// Positions           // Colors          // Texture Coords
	// Front face
	-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // Bottom-right
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	-0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Top-left
	-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left

	// Back face
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Top-left
	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Bottom-right
	-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left

	// Left face
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  // Top-left
	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left

	// Right face
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left
	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Top-left
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
	 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // Bottom-right
	 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left

	 // Top face
	 -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
	  0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
	  0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	  0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	 -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // Top-left
	 -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left

	 // Bottom face
	 -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
	 -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
	  0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	  0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  // Top-right
	  0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  // Top-left
	 -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
};
size_t vertices_simple_size = sizeof(vertices_simple);

float vertices_simple_face[] = {
	// Positions          // Colors           // Texture Coordinates
	-0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
	0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
	0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Top-right
	-0.5f, 0.5f, 0.5f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top-left
};
size_t vertices_simple_face_size = sizeof(vertices_simple_face);

// Vertex Shader Source
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"void main() {\n"
"	 vec3 pos = aPos;\n"
"    gl_Position = projection * view * model * vec4(pos, 1);\n"
"    ourColor = aColor;\n"
"}\n";

// Fragment Shader Source
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main() {\n"
"    FragColor = vec4(ourColor, 1);\n"
"}\n";

// Vertex Shader Source with texture!!
const char* vertexTextureShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"  // Change to vec2 for texture coordinates
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"    ourColor = aColor;\n"
"    TexCoord = aTexCoord;\n"  // Add the semicolon here
"}\n";

// Fragment Shader Source
const char* fragmentTextureShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"  // Texture coordinates passed from the vertex shader
"uniform sampler2D texture1;\n"  // The texture
"void main() {\n"
"    vec4 textureColor = texture(texture1, TexCoord);  // Sample the texture\n"
"    FragColor = textureColor * vec4(ourColor, 1.0);  // Combine texture color with vertex color\n"
"}\n";