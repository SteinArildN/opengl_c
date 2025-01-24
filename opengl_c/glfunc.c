#include "glfunc.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint OPENGLcompile_shader(const char* vert, const char* frag) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void OPENGLsetup_buffers_simple(glSimpleBuffers* buffers, glSimpleBufferContent* content, int is_textured) {
	// Generate and bind buffers
	glGenVertexArrays(1, &buffers->VAO);
	glGenBuffers(1, &buffers->VBO);

	glBindVertexArray(buffers->VAO);

	// Bind and buffer the vertex data (positions, colors, and texture coordinates)
	glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
	glBufferData(GL_ARRAY_BUFFER, content->vertices_size, content->vertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position (3 floats)
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color (3 floats)
	glEnableVertexAttribArray(1);

	if (is_textured != 0) {
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture coordinates (2 floats)
		glEnableVertexAttribArray(2);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OPENGLsetup_buffers(glBuffers* buffers, glBufferContent* content, int is_textured) {
	// Generate and bind buffers
	glGenVertexArrays(1, &buffers->VAO);
	glGenBuffers(1, &buffers->VBO);
	glGenBuffers(1, &buffers->EBO);

	glBindVertexArray(buffers->VAO);

	// Bind and buffer the vertex data (positions, colors, and texture coordinates)
	glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
	glBufferData(GL_ARRAY_BUFFER, content->vertices_size, content->vertices, GL_STATIC_DRAW);

	// Bind and buffer the index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, content->indices_size, content->indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position (3 floats)
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color (3 floats)
	glEnableVertexAttribArray(1);

	if (is_textured != 0) {
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture coordinates (2 floats)
		glEnableVertexAttribArray(2);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OPENGLbindUniform_Mat4f(GLuint program, const char* field, mat4f data) {
	GLint location = glGetUniformLocation(program, field);
	glUniformMatrix4fv(location, 1, GL_FALSE, &data.m[0][0]);
}

GLuint OPENGLloadTexture(const char* filename) {
	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (!data) {
		printf("Failed to load texture: %s\n", stbi_failure_reason());
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Determine format (e.g., RGB or RGBA)
	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

	// Upload texture to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering to nearest neighbor
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/

	// Free stb_image data
	stbi_image_free(data);

	return texture;
}