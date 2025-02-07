#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <math.h>
#define PI 3.14159265358979323846

#include <time.h>

//silly data
float vertices[] = {
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

// Vertex Shader Source with texture!!
const char* vertex_source =
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
const char* fragment_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"  // Texture coordinates passed from the vertex shader
"uniform sampler2D texture1;\n"  // The texture
"void main() {\n"
"    vec4 textureColor = texture(texture1, TexCoord);  // Sample the texture\n"
"    FragColor = textureColor * vec4(ourColor, 1.0);  // Combine texture color with vertex color\n"
"}\n";

//opperationsss
int int_random(int min, int max) {
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

//math
typedef struct {
	float f[2];
} vec2;
typedef struct {
	float f[3];
} vec3;
typedef struct {
	float f[4];
} vec4;
typedef struct {
	float m[4][4];
} mat4;

vec3 vector_combine(vec3 a, vec3 b) {
	vec3 result = { 0 };
	for (int i = 0; i < 3; i++) result.f[i] = a.f[i] + b.f[i];
	return result;
}
vec3 vector_scalar(vec3 a, float b) {
	vec3 result = { 0 };
	for (int i = 0; i < 3; i++) result.f[i] = a.f[i] * b;
	return result;
}
vec3 vector_multi(vec3 a, vec3 b) {
	vec3 result = { 0 };
	for (int i = 0; i < 3; i++) result.f[i] = a.f[i] * b.f[i];
	return result;
}
int vector_equal(vec3 a, vec3 b) {
	return (
		a.f[0] == b.f[0] &&
		a.f[1] == b.f[1] &&
		a.f[2] == b.f[2]
		);
}
mat4 matrix_identity() {
	mat4 result = { 0 };
	for (int i = 0; i < 4; i++) result.m[i][i] = 1;
	return result;
}
mat4 matrix_fromVector(vec3 vec) {
	mat4 mat = matrix_identity();
	for (int i = 0; i < 3; i++) mat.m[3][i] = vec.f[i];
	return mat;
}
mat4 matrix_scalarMulti(mat4 a, float scalar) {
	mat4 result = { 0 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = a.m[i][j] * scalar;
	return result;
}
mat4 matrix_matMulti(mat4 a, mat4 b) {
	mat4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return result;
}
mat4 matrix_rotate(mat4 mat, vec4 axis_angle) { //ty chatgpt
	vec3 axis = { { axis_angle.f[0], axis_angle.f[1], axis_angle.f[2] } };
	float angle = axis_angle.f[3];

	// Normalize the rotation axis
	float axis_length = sqrt(axis.f[0] * axis.f[0] + axis.f[1] * axis.f[1] + axis.f[2] * axis.f[2]);
	axis.f[0] /= axis_length;
	axis.f[1] /= axis_length;
	axis.f[2] /= axis_length;

	// Precompute sine and cosine
	float cos_theta = cos(angle);
	float sin_theta = sin(angle);
	float one_minus_cos = 1.0f - cos_theta;

	// Rotation matrix components
	float x = axis.f[0], y = axis.f[1], z = axis.f[2];
	mat4 rotation = { 0 };
	rotation.m[0][0] = cos_theta + x * x * one_minus_cos;
	rotation.m[0][1] = x * y * one_minus_cos - z * sin_theta;
	rotation.m[0][2] = x * z * one_minus_cos + y * sin_theta;
	rotation.m[0][3] = 0.0f;

	rotation.m[1][0] = y * x * one_minus_cos + z * sin_theta;
	rotation.m[1][1] = cos_theta + y * y * one_minus_cos;
	rotation.m[1][2] = y * z * one_minus_cos - x * sin_theta;
	rotation.m[1][3] = 0.0f;

	rotation.m[2][0] = z * x * one_minus_cos - y * sin_theta;
	rotation.m[2][1] = z * y * one_minus_cos + x * sin_theta;
	rotation.m[2][2] = cos_theta + z * z * one_minus_cos;
	rotation.m[2][3] = 0.0f;

	rotation.m[3][0] = 0.0f;
	rotation.m[3][1] = 0.0f;
	rotation.m[3][2] = 0.0f;
	rotation.m[3][3] = 1.0f;

	// Multiply the input matrix with the rotation matrix
	return matrix_matMulti(mat, rotation);
}
mat4 matrix_perspective(float fov, float aspect, float near, float far) {
	mat4 mat = { {{0}} };
	float tanHalfFOV = tanf(fov / 2.0f);
	mat.m[0][0] = 1.0f / (aspect * tanHalfFOV);
	mat.m[1][1] = 1.0f / tanHalfFOV;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[2][3] = -1.0f;
	mat.m[3][2] = -(2.0f * far * near) / (far - near);

	// Ensure other values are zero
	mat.m[0][1] = mat.m[0][2] = mat.m[0][3] = 0.0f;
	mat.m[1][0] = mat.m[1][2] = mat.m[1][3] = 0.0f;
	mat.m[2][0] = mat.m[2][1] = 0.0f;
	mat.m[3][0] = mat.m[3][1] = mat.m[3][3] = 0.0f;

	return mat;
}
//lol
mat4 matrix_translate(mat4 mat, vec3 vec) {
	return matrix_matMulti(mat, matrix_fromVector(vec));
}
mat4 matrix_scale(mat4 mat, vec3 scale) {
	mat4 result = mat;
	for (int i = 0; i < 3; i++) result.m[i][i] *= scale.f[i];
	return result;
}
vec3 dir_vector(vec3 rot, vec3 offset, int simple) {
	vec3 rotation_radians = {
	(rot.f[0] + offset.f[0]) * (PI / 180),
	(rot.f[1] + offset.f[1]) * (PI / 180),
	(rot.f[2] + offset.f[2]) * (PI / 180)
	};

	float pitch = rotation_radians.f[0];
	float yaw = rotation_radians.f[1];
	vec3 direction_vector = { 0 };
	if (simple == 0) {
		direction_vector.f[0] = sinf(yaw);
		direction_vector.f[2] = cosf(yaw);
	}
	else {
		direction_vector.f[0] = cosf(pitch) * sinf(yaw);
		direction_vector.f[1] = sinf(-pitch);
		direction_vector.f[2] = cosf(pitch) * cosf(yaw);
	}
	return direction_vector;
}

//camera
struct camera {
	vec3 pos;
	vec3 rot;
	vec3 vel;
	int flymode;
	int j;
};

mat4 camera_toMatrix(struct camera* camera_pointer) {
	mat4 result = matrix_identity();
	result = matrix_translate(result, (vec3) {
		-camera_pointer->pos.f[0],
		-camera_pointer->pos.f[1],
		-camera_pointer->pos.f[2]
	});
	vec3 rotation_radians = {
		camera_pointer->rot.f[0] * (PI / 180),
		camera_pointer->rot.f[1] * (PI / 180),
		camera_pointer->rot.f[2] * (PI / 180)
	};
	result = matrix_rotate(result, (vec4) { 0, 1, 0, (rotation_radians.f[1]) });
	result = matrix_rotate(result, (vec4) { 1, 0, 0, (rotation_radians.f[0]) });
	result = matrix_rotate(result, (vec4) { 0, 0, 1, (rotation_radians.f[2]) });
	return result;
}
void camera_normalize(struct camera* camera_pointer) {
	while (camera_pointer->rot.f[0] < -180) camera_pointer->rot.f[0] += 360;
	while (camera_pointer->rot.f[0] > 180) camera_pointer->rot.f[0] -= 360;
	while (camera_pointer->rot.f[1] < -180) camera_pointer->rot.f[1] += 360;
	while (camera_pointer->rot.f[1] > 180) camera_pointer->rot.f[1] -= 360;
	while (camera_pointer->rot.f[2] < -180) camera_pointer->rot.f[2] += 360;
	while (camera_pointer->rot.f[2] > 180) camera_pointer->rot.f[2] -= 360;
}
void camera_clamp(struct camera* camera_pointer) {
	if (camera_pointer->rot.f[0] < -180) camera_pointer->rot.f[1] = -180;
	if (camera_pointer->rot.f[0] > 180) camera_pointer->rot.f[1] = 180;
}
void camera_rotate(struct camera* camera_pointer, vec3 rot) {
	for (int i = 0; i < 3; i++) camera_pointer->rot.f[i] += rot.f[i];
	camera_clamp(camera_pointer);
	camera_normalize(camera_pointer);
}
void camera_move(struct camera* camera_pointer, float str, float offset, int simple) {
	vec3 direction_vector = dir_vector(camera_pointer->rot, (vec3) { 0, offset, 0 }, simple);
	direction_vector = vector_scalar(direction_vector, -str);
	//camera_pointer->pos = vector_combine(camera_pointer->pos, direction_vector);
	camera_pointer->vel = vector_combine(camera_pointer->vel, direction_vector);
}
void camera_add_velocity(struct camera* camera_pointer, vec3 vel) {
	camera_pointer->vel.f[1] += vel.f[1];
	camera_pointer->vel.f[0] += vel.f[0];
	camera_pointer->vel.f[2] += vel.f[2];
}
int camera_collision(vec3 cube, vec3 camera, vec3 camera_size) {
	float offset = 0.5f; // Cube extends from (cube - 0.5) to (cube + 0.5)
	return (
		camera.f[0] - camera_size.f[0] <= cube.f[0] + offset &&
		camera.f[0] + camera_size.f[0] >= cube.f[0] - offset &&
		camera.f[1] - camera_size.f[1] <= cube.f[1] + offset &&
		camera.f[1] + camera_size.f[1] >= cube.f[1] - offset &&
		camera.f[2] - camera_size.f[2] <= cube.f[2] + offset &&
		camera.f[2] + camera_size.f[2] >= cube.f[2] - offset
		);
}

//fun
#define FACE_FRONT  (1 << 0)
#define FACE_BACK   (1 << 1)
#define FACE_LEFT   (1 << 2)
#define FACE_RIGHT  (1 << 3)
#define FACE_TOP    (1 << 4)
#define FACE_BOTTOM (1 << 5)
#define FACE_ALL (FACE_FRONT | FACE_BACK | FACE_LEFT | FACE_RIGHT | FACE_TOP | FACE_BOTTOM)
struct cube {
	vec3 pos;
	int type;
	int dormant;
	int draw_face;
};
#define cubes_size 32768
struct cube cubes[cubes_size] = { 0 }; //big number so we dont go out of bounds
void spawn_cube(vec3 pos, vec3 rot) {
	for (int i = 30000; i < cubes_size; i++) {
		if (cubes[i].type == 0) {
			vec3 pos_calc = vector_combine(pos, vector_scalar(dir_vector(rot, (vec3){0,0,0}, 1), -2));
			cubes[i] = (struct cube){ pos_calc, 1, 0, FACE_ALL };
			//cubes[i] = (struct cube){ pos, 1, 0, FACE_ALL };
			return;
		}
	}
}
void spawn_cube_excact(vec3 pos) {
	for (int i = 30000; i < cubes_size; i++) {
		if (cubes[i].type == 0) {
			cubes[i].pos = pos;
			cubes[i].draw_face == FACE_ALL;
			return;
		}
	}
}
#define world_x 32
#define world_y 32
#define world_z 32
void create_world() {
	int index = 0;
	for (int x = 0; x < world_x; x++)
		for (int y = 0; y < world_y; y++)
			for (int z = 0; z < world_z; z++) {
				index = x + y * world_x + z * world_x * world_y;
				cubes[index].pos = (vec3){ x,y,z };
				cubes[index].type = int_random(0, 1);
				//cubes[index].type = 1;
			}
}
void optimize_world() {
	int index = 0;
	for (int i = 0; i < cubes_size; i++)
		cubes[i].draw_face = 0;
	for (int x = 0; x < world_x; x++)
		for (int y = 0; y < world_y; y++)
			for (int z = 0; z < world_z; z++) {
				index = x + y * world_x + z * world_x * world_y;
				if (x == 0 || cubes[index - 1].type == 0) cubes[index].draw_face |= FACE_LEFT;
				if (x == world_x - 1 || cubes[index + 1].type == 0) cubes[index].draw_face |= FACE_RIGHT;
				if (y == 0 || cubes[index - world_x].type == 0) cubes[index].draw_face |= FACE_BOTTOM;
				if (y == world_y - 1 || cubes[index + world_x].type == 0) cubes[index].draw_face |= FACE_TOP;
				if (z == 0 || cubes[index - world_x * world_y].type == 0) cubes[index].draw_face |= FACE_BACK;
				if (z == world_z - 1 || cubes[index + world_x * world_y].type == 0) cubes[index].draw_face |= FACE_FRONT;
			}
}
int collision(vec3 blockpos, vec3 raycastpos, float offset) {
	return (
		raycastpos.f[0] >= blockpos.f[0] - offset && raycastpos.f[0] <= blockpos.f[0] + offset &&
		raycastpos.f[1] >= blockpos.f[1] - offset && raycastpos.f[1] <= blockpos.f[1] + offset &&
		raycastpos.f[2] >= blockpos.f[2] - offset && raycastpos.f[2] <= blockpos.f[2] + offset
		);
}

void raycast_world(vec3 pos, vec3 rot, int range, int action) {
	vec3 rpos = { 0 };
	vec3 rotation_radians = {
		rot.f[0]* (PI / 180),
		rot.f[1] * (PI / 180),
		rot.f[2] * (PI / 180)
	};
	float pitch = rotation_radians.f[0];
	float yaw = rotation_radians.f[1];
	vec3 initial_direction_vector = {
		initial_direction_vector.f[0] = cosf(pitch) * sinf(yaw),
		initial_direction_vector.f[1] = sinf(-pitch),
		initial_direction_vector.f[2] = cosf(pitch) * cosf(yaw)
	};
	for (int i = 0; i < range; i++) {
		vec3 direction_vector = vector_scalar(initial_direction_vector, -1 * i);
		rpos = vector_combine(pos, direction_vector);
		for (int j = 0; j < cubes_size; j++) {
			if (collision(cubes[j].pos, rpos, 0.5)) {
				if (cubes[j].type == 1) {
					cubes[j].type = 0;
					return;
				}
			}
		}
	}
}
//hihi
void jump(struct camera* camera_pointer, float str) {
	if (camera_pointer->j < 3)
		camera_pointer->vel.f[1] = str;
}
void camera_logic(struct camera* camera_pointer, int noclip) {
	//y
	camera_pointer->j++;
	if (!camera_pointer->flymode)
		camera_pointer->vel.f[1] -= 0.0025;
	camera_pointer->pos.f[1] += camera_pointer->vel.f[1];
	for (int i = 0; i < cubes_size; i++) {
		if (cubes[i].type == 0)
			continue;
		if (noclip)
			continue;
		if (camera_collision(cubes[i].pos, camera_pointer->pos, (vec3) { 0.25,0.25,0.25 })) {
			camera_pointer->pos.f[1] -= camera_pointer->vel.f[1] * 1;
			if (camera_pointer->vel.f[1] < 0)
				camera_pointer->j = 0;
			camera_pointer->vel.f[1] = 0;
		}
	}
	if (camera_pointer->flymode)
		camera_pointer->vel.f[1] *= 0.8;
	//x
	camera_pointer->pos.f[0] += camera_pointer->vel.f[0];
	for (int i = 0; i < cubes_size; i++) {
		if (cubes[i].type == 0)
			continue;
		if (noclip)
			continue;
		if (camera_collision(cubes[i].pos, camera_pointer->pos, (vec3) { 0.25, 0.25, 0.25 })) {
			camera_pointer->pos.f[0] -= camera_pointer->vel.f[0] * 1.1;
			camera_pointer->vel.f[0] = 0;
		}
	}
	camera_pointer->vel.f[0] *= 0.8;
	//z
	camera_pointer->pos.f[2] += camera_pointer->vel.f[2];
	for (int i = 0; i < cubes_size; i++) {
		if (cubes[i].type == 0)
			continue;
		if (noclip)
			continue;
		if (camera_collision(cubes[i].pos, camera_pointer->pos, (vec3) { 0.25, 0.25, 0.25 })) {
			camera_pointer->pos.f[2] -= camera_pointer->vel.f[2] * 1.1;
			camera_pointer->vel.f[2] = 0;
		}
	}
	camera_pointer->vel.f[2] *= 0.8;
}

//balls
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s..", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	struct camera* camera_pointer = glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
		spawn_cube(camera_pointer->pos, camera_pointer->rot);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		raycast_world(camera_pointer->pos, camera_pointer->rot, 4, 0);
		optimize_world();
	}
}

void key_repeat(GLFWwindow* window) {
	struct camera* camera_pointer = glfwGetWindowUserPointer(window);
	float sens = 0.01;
	//rotate
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		camera_rotate(camera_pointer, (vec3) { 0, 2, 0 });
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		camera_rotate(camera_pointer, (vec3) { 0, -2, 0 });
	if (glfwGetKey(window, GLFW_KEY_UP))
		camera_rotate(camera_pointer, (vec3) { 2, 0, 0 });
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		camera_rotate(camera_pointer, (vec3) { -2, 0, 0 });
	//move
	if (glfwGetKey(window, GLFW_KEY_W))
		camera_move(camera_pointer, sens, 0, camera_pointer->flymode);
	if (glfwGetKey(window, GLFW_KEY_S))
		camera_move(camera_pointer, -sens, 0, camera_pointer->flymode);
	if (glfwGetKey(window, GLFW_KEY_A))
		camera_move(camera_pointer, sens, 90, 0);
	if (glfwGetKey(window, GLFW_KEY_D))
		camera_move(camera_pointer, -sens, 90, 0);
	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		if (camera_pointer->flymode)
			camera_add_velocity(camera_pointer, (vec3) { 0, sens, 0 });
		else
			jump(camera_pointer, sens * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
		if (camera_pointer->flymode)
			camera_add_velocity(camera_pointer, (vec3) { 0, -sens, 0 });
	}
}
//gl
GLuint OPENGLcompileshader(const char* vert, const char* frag) {
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vert, NULL);
	glCompileShader(vertex_shader);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag, NULL);
	glCompileShader(fragment_shader);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

void OPENGLsetupbuffers(GLuint* VAO, GLuint* VBO) {
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
	return texture;
}

void OPENGLbind_mat4(GLuint program, const char* field, mat4 mat) {
	GLint location = glGetUniformLocation(program, field);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat.m[0][0]);
}

//main script
int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "failed to init glfw");
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "lol", NULL, NULL);
	if (!window) {
		fprintf(stderr, "failed to create window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLuint shaderprogram = OPENGLcompileshader(vertex_source, fragment_source);
	GLuint VAO, VBO;
	OPENGLsetupbuffers(&VAO, &VBO);

	GLuint textures[2] = {
		OPENGLloadTexture("test.png"),
		OPENGLloadTexture("stone.png")
	};

	int width, height;
	float ratio;
	double time;

	struct camera player_camera = {
		{world_x / 2,world_y + 10,world_z / 2},
		{0,0,0},
		{0,0,0}, //vel
		0, //flymode
		0
	};
	glfwSetWindowUserPointer(window, &player_camera);

	glEnable(GL_DEPTH_TEST);

	create_world();
	optimize_world();
	spawn_cube_excact((vec3) { -3, -3, -3 });

	while (!glfwWindowShouldClose(window)) {
		glfwSetKeyCallback(window, key_callback);
		key_repeat(window);

		glfwGetFramebufferSize(window, &width, &height);
		ratio = (float)width / (float)height;
		time = glfwGetTime();

		//game
		camera_logic(&player_camera, 0);
		if (player_camera.pos.f[1] < -100)
			player_camera.pos.f[1] = 100;

		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.1, 0.15, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 projection = matrix_perspective(70.f, ratio, 0.1f, 100.f);
		//projection = matrix_invert_y(projection);d
		OPENGLbind_mat4(shaderprogram, "projection", projection);
		mat4 view = matrix_identity();
		view = camera_toMatrix(&player_camera);
		//view = matrix_invert_y(view);
		OPENGLbind_mat4(shaderprogram, "view", view);
		fprintf(stderr, "player pos { %.f, ", player_camera.pos.f[0]);
		fprintf(stderr, "%.f, ", player_camera.pos.f[1]);
		fprintf(stderr, "%.f } - player rot { ", player_camera.pos.f[2]);
		fprintf(stderr, "%.f, ", player_camera.rot.f[0]);
		fprintf(stderr, "%.f, ", player_camera.rot.f[1]);
		fprintf(stderr, "%.f }\n", player_camera.rot.f[2]);

		glUseProgram(shaderprogram);
		for (int i = 0; i < cubes_size; i++) {
			if (cubes[i].type == 0 || cubes[i].dormant == 1)
				continue;
			mat4 model = matrix_identity();
			//model = matrix_rotate(model, (vec4) { 0.1, 0.2, 0.3, (float)time });
			model = matrix_translate(model, cubes[i].pos);
			OPENGLbind_mat4(shaderprogram, "model", model);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[cubes[i].type]);
			glUniform1i(glGetUniformLocation(shaderprogram, "texture1"), 0);
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			if (cubes[i].draw_face & FACE_FRONT)
				glDrawArrays(GL_TRIANGLES, 0, 6);
			if (cubes[i].draw_face & FACE_BACK)
				glDrawArrays(GL_TRIANGLES, 6, 6);
			if (cubes[i].draw_face & FACE_LEFT)
				glDrawArrays(GL_TRIANGLES, 12, 6);
			if (cubes[i].draw_face & FACE_RIGHT)
				glDrawArrays(GL_TRIANGLES, 18, 6);
			if (cubes[i].draw_face & FACE_TOP)
				glDrawArrays(GL_TRIANGLES, 24, 6);
			if (cubes[i].draw_face & FACE_BOTTOM)
				glDrawArrays(GL_TRIANGLES, 30, 6);
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glfwSwapInterval(1.5);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(&shaderprogram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
