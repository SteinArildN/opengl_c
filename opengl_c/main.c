#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "glfunc.h"
#include "game.h"

void create_cube(vec3f array[64], vec3f rot, vec3f pos) {
	for (int i = 0; i < 3; i++) pos.f[i] *= -1;
	rot.f[0] *= -1; rot.f[1] *= 2; rot.f[2] *= -1;
	for (int i = 0; i < 64; i++) {
		if (array[i].f[0] == 0 && array[i].f[1] == 0 && array[i].f[2] == 0) {
			array[i] = vec3f_combine(quick_vector_calc(rot, 10), pos);
			//array[i] = pos;
			//array[i] = quick_vector_calc(rot, 1);
			fprintf(stderr, "cube created at index %.f\n", (float)i);
			for (int j = 0; j < 3; j++) {
				fprintf(stderr, "pos: %.f\n", array[i].f[0]);
			}
			break;
		}
		else {
			printf(stderr, "no cube created");
		}
	}
}

void print_matrix(mat4f mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fprintf(stderr, "{ %.2f }", mat.m[i][j] );
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "\n");
}

//CALLBACK FUNCTIONS
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW.\n");
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "opengl in c", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window.\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLuint texture = OPENGLloadTexture("stone.png");
	GLuint CUBEshaderProgram = OPENGLcompile_shader(vertexTextureShaderSource, fragmentTextureShaderSource);
	glSimpleBuffers buffers;
	glSimpleBufferContent content = {
		vertices_simple,
		vertices_simple_size
	};
	OPENGLsetup_buffers_simple(&buffers, &content, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	double time;
	int width, height;
	struct camera cam = {
		{0,0,0},
		{0,0,0}
	};
	glfwSetWindowUserPointer(window, &cam);

	int lol = 0;
	vec3f cubes[64] = {0};

	while (!glfwWindowShouldClose(window)) {
		glfwSetKeyCallback(window, key_callback);
		key_loop(window);

		time = glfwGetTime();
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;
		
		glViewport(0, 0, width, height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4f projection = matrix_createPerspective(70.f, ratio, 0.1f, 100.f);
		mat4f view = matrix_identity();

		view = camera_to_matrix(&cam);

		glUseProgram(CUBEshaderProgram);

		OPENGLbindUniform_Mat4f(CUBEshaderProgram, "projection", projection);
		OPENGLbindUniform_Mat4f(CUBEshaderProgram, "view", view);

		lol++;
		//fprintf(stderr, "lol is now: %.f\n", (float)lol);
		if (lol > 100) {
			create_cube(cubes, cam.rot, cam.pos);
			lol = 0;
		}

		for (int i = 0; i < 64; i++) {
			if (cubes[i].f[0] == 0 && cubes[i].f[1] == 0 && cubes[i].f[2] == 0) continue;
			mat4f model = matrix_identity();
			model = matrix_scale(model, (vec3f) { 1, 0.2, 0.5 });
			model = matrix_rotate(model, (vec4f) { 0.9, 0.6, 0.3, (float)time });
			model = matrix_translate(model, cubes[i]);
			//and the bind the model to the shader program
			OPENGLbindUniform_Mat4f(CUBEshaderProgram, "model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(CUBEshaderProgram, "texture1"), 0); // Texture unit 0

			glBindVertexArray(buffers.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		vec3f positions[4] = {
			{2,0,0},
			{-2,0,0},
			{0,0,2},
			{0,0,-2}
		};
		
		for (int i = 0; i < 4; i++) {
			mat4f model = matrix_identity();
			model = matrix_scale(model, (vec3f) { 1, 0.2, 0.5 });
			model = matrix_rotate(model, (vec4f) { 0.9, 0.6, 0.3, (float)time });
			model = matrix_translate(model, positions[i]);
			//and the bind the model to the shader program
			OPENGLbindUniform_Mat4f(CUBEshaderProgram, "model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(glGetUniformLocation(CUBEshaderProgram, "texture1"), 0); // Texture unit 0

			glBindVertexArray(buffers.VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		


		glfwSwapInterval(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &buffers.VAO);
	glDeleteBuffers(1, &buffers.VBO);
	glDeleteProgram(CUBEshaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}