#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "glfunc.h"

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
	glfwSetErrorCallback(error_callback); //set callback func

	//init glfw
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW.\n");
	}

	//create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "opengl in c", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window.\n");
		glfwTerminate();
	}

	//make context, do all gl after this
	//prob add message if fails
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	//various gl variables we need to declare for late use
	//texture that we load and pass to opengl later
	GLuint texture = OPENGLloadTexture("stone.png");
	//compile our vert and frag shader into progam (for cubes)
	GLuint CUBEshaderProgram = OPENGLcompile_shader(vertexTextureShaderSource, fragmentTextureShaderSource);
	//creating empty buffers, and specifying what data they should have (cubes)
	glSimpleBuffers buffers;
	glSimpleBufferContent content = {
		vertices_simple,
		vertices_simple_size
	};
	//this sets up our buffer with the buffer and content struct
	OPENGLsetup_buffers_simple(&buffers, &content, 1);

	//enable some coooool things
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	//set some 'global' variables
	double time;
	int width, height;

	//loop
	while (!glfwWindowShouldClose(window)) {
		//sets func in which to call for input
		glfwSetKeyCallback(window, key_callback);

		time = glfwGetTime();
		glfwGetFramebufferSize(window, &width, &height); //we constantly get the window size, as it can be changed
		const float ratio = width / (float)height; //also the ratio, we use it for projection
		
		//set the view port, tells gl how big 'its canvas' is
		glViewport(0, 0, width, height);
		//set the clear/bg color, and clear it along side depth buffer bit
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//these *will* be universal matricies
		//projection converts our scene into gl's projection matrix
		//view is basically our camera
		mat4f projection = matrix_createPerspective(70.f, ratio, 0.1f, 100.f);
		mat4f view = matrix_identity();

		//use our cube program, because we are now going to draw cubes
		glUseProgram(CUBEshaderProgram);

		//time to bind the projection matrix in our shader program
		OPENGLbindUniform_Mat4f(CUBEshaderProgram, "projection", projection);
		//and the view matrix
		OPENGLbindUniform_Mat4f(CUBEshaderProgram, "view", view);

		/*
		//Loop for 'creating cubes' start:
		*/

		//now we create our model matrix, which will differ from each other
		//i also apply som manipulations to the matrix. follow this order s-r-t as to not have them mess with each other
		mat4f model = matrix_identity();
		model = matrix_scale(model, (vec3f) { 1, 0.2, 0.5 });
		model = matrix_rotate(model, (vec4f) { 0.9, 0.6, 0.3, (float)time });
		model = matrix_translate(model, (vec3f) { 0, 0, -2 });
		//and the bind the model to the shader program
		OPENGLbindUniform_Mat4f(CUBEshaderProgram, "model", model);

		//before we draw our cube, we first activate unit 0 of gl_textures
		glActiveTexture(GL_TEXTURE0);
		//and bind it to the previosly loaded texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set the uniform for the texture in the shader
		glUniform1i(glGetUniformLocation(CUBEshaderProgram, "texture1"), 0); // Texture unit 0

		//bind the VAO that holds the VBO
		glBindVertexArray(buffers.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36); //finally we draw the cube

		// Unbind VAO and texture - avoids silly erors
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		//set swap itnerval so we dont use stupid amount of computer
		glfwSwapInterval(1);
		glfwSwapBuffers(window); //swap the front with back
		glfwPollEvents();
	}

	//general cleanup. i already do bad conversion and dont really manage memory but i dont give a fuck
	glDeleteVertexArrays(1, &buffers.VAO);
	glDeleteBuffers(1, &buffers.VBO);
	glDeleteProgram(CUBEshaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	//return :)
	return 0;
}
