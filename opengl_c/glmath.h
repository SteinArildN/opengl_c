#pragma once
#include <math.h>
#define balls 3.14159265358979323846

//MATH
typedef struct {
	float f[2];
} vec2f;
typedef struct {
	float f[3];
} vec3f;
typedef struct {
	float f[4];
} vec4f;
typedef struct {
	float m[4][4];
} mat4f;

inline vec3f vec3f_combine(vec3f a, vec3f b) {
	vec3f result;
	for (int i = 0; i < 3; i++) result.f[i] = a.f[i] + b.f[i];
	return result;
}

inline mat4f matrix_identity() {
	mat4f mat = { 0 }; for (int i = 0; i < 4; i++) mat.m[i][i] = 1;
	return mat;
}

inline mat4f matrix_fromVector(vec3f vec) {
	mat4f mat = matrix_identity();
	for (int i = 0; i < 3; i++) mat.m[3][i] = vec.f[i];
	return mat;
}

inline mat4f matrix_createPerspective(float fov, float aspect, float near, float far) {
	mat4f mat = { {{0}} };
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

//ty chatgpt
inline float matrix_dotProduct(vec3f a, vec3f b) {
	float result = 0.0f;
	for (int i = 0; i < 3; i++) {
		result += a.f[i] * b.f[i]; // Multiply corresponding components and sum
	}
	return result;
}

inline vec3f matrix_crossProduct(vec3f a, vec3f b) {
	vec3f result;
	result.f[0] = a.f[1] * b.f[2] - a.f[2] * b.f[1];
	result.f[1] = a.f[2] * b.f[0] - a.f[0] * b.f[2];
	result.f[2] = a.f[0] * b.f[1] - a.f[1] * b.f[0];
	return result;
}

inline vec4f matrix_vectorMulti(mat4f a, vec4f b) {
	vec4f result = { 0 }; // Initialize result vector to 0
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.f[i] += a.m[i][j] * b.f[j]; // Perform dot product of matrix row and vector
		}
	}
	return result;
}

inline mat4f matrix_scalarMulti(mat4f a, float scalar) {
	mat4f result = { 0 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.m[i][j] = a.m[i][j] * scalar;
	return result;
}

inline mat4f matrix_matMulti(mat4f a, mat4f b) {
	mat4f result = { 0 }; // Initialize result matrix to 0
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += a.m[i][k] * b.m[k][j]; // Multiply row of `a` by column of `b`
			}
		}
	}
	return result;
}

//thanks chatgpt
inline mat4f matrix_rotate(mat4f mat, vec4f axis_angle) {
	vec3f axis = { { axis_angle.f[0], axis_angle.f[1], axis_angle.f[2] } };
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
	mat4f rotation = { 0 };
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

inline mat4f matrix_translate(mat4f mat, vec3f vector) {
	mat4f new_vec = matrix_fromVector(vector);
	return matrix_matMulti(mat, new_vec);
}

inline mat4f matrix_scale(mat4f mat, vec3f vector) {
	mat4f result = mat;
	for (int i = 0; i < 3; i++) result.m[i][i] *= vector.f[i];
	return result;
}