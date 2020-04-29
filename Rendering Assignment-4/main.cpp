/*
Refrence:
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "skybox.h"
#include "maths_funcs.h"

#include "loader.h"

#include <windows.h>
#include <mmsystem.h>

int width = 800;
int height = 600;

GLuint SkyBoxShaderProgramID;
GLuint ReflectionShaderProgramID;
GLuint RefractionShaderProgramID;
GLuint FresnelShaderProgramID;
GLuint ChromaticShaderProgramID;
GLuint ShaderProgramID;
GLuint textureID;
GLuint tid;

GLuint skyboxVAO;
GLuint skyboxVBO;
GLuint objectVAO = 0;
GLuint objectVBO = 0;
GLuint objectNormalVBO = 0;

GLuint objectloc1;
GLuint objectloc2;
GLuint objectloc3;
GLuint objectloc4;
GLuint objectloc5;

GLuint skyboxloc1;


GLfloat rotateAnglex = 0.1f;
GLfloat rotateAngley = 0.0f;
GLfloat rotateAnglez = 0.1f;

GLfloat lightPosx = 1.2f;
GLfloat lightPosy = -3.0f;
GLfloat lightPosz = 3.5f;

GLfloat rotatez = 0.0f;
float objSize = -265.0f;
int imageLoadFlag = 0;

char OutputFlag = 'm';

// Cube Vertices, Normals and UV Values
std::vector<glm::vec3> obj1_vertices = {
	   glm::vec3(-0.5, -0.5, 0.5),
	   glm::vec3(0.5, -0.5, 0.5),
	   glm::vec3(-0.5,  0.5, 0.5),
	   glm::vec3(0.5,  0.5, 0.5),
	   glm::vec3(-0.5,  0.5, 0.5),
	   glm::vec3(0.5, -0.5, 0.5),
	   glm::vec3(0.5, -0.5, 0.5),
	   glm::vec3(0.5, -0.5, -0.5),
	   glm::vec3(0.5,  0.5, 0.5),
	   glm::vec3(0.5,  0.5, -0.5),
	   glm::vec3(0.5,  0.5, 0.5),
	   glm::vec3(0.5, -0.5, -0.5),
	   glm::vec3(-0.5, -0.5, -0.5),
	   glm::vec3(-0.5,  0.5, -0.5),
	   glm::vec3(0.5, -0.5, -0.5),
	   glm::vec3(0.5,  0.5, -0.5),
	   glm::vec3(0.5, -0.5, -0.5),
	   glm::vec3(-0.5,  0.5, -0.5),
	   glm::vec3(-0.5, -0.5, 0.5),
	   glm::vec3(-0.5,  0.5, 0.5),
	   glm::vec3(-0.5, -0.5, -0.5),
	   glm::vec3(-0.5,  0.5, -0.5),
	   glm::vec3(-0.5, -0.5, -0.5),
	   glm::vec3(-0.5,  0.5, 0.5),
	   glm::vec3(-0.5, -0.5, 0.5),
	   glm::vec3(-0.5, -0.5, -0.5),
	   glm::vec3(0.5, -0.5, 0.5),
	   glm::vec3(0.5, -0.5, -0.5),
	   glm::vec3(0.5, -0.5, 0.5),
	   glm::vec3(-0.5, -0.5, -0.5),
	   glm::vec3(-0.5,  0.5, 0.5),
	   glm::vec3(0.5,  0.5, 0.5),
	   glm::vec3(-0.5,  0.5, -0.5),
	   glm::vec3(0.5,  0.5, -0.5),
	   glm::vec3(-0.5,  0.5, -0.5),
	   glm::vec3(0.5,  0.5, 0.5)
};

std::vector<glm::vec2> obj1_uvs = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
};

std::vector<glm::vec3> obj1_normals = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
};

float cube_vertex_count = 36;
std::vector<glm::vec3> obj1_tangents;
std::vector<glm::vec3> obj1_bitangents;

//LoadObj Object1("Object/cube.obj", obj1_vertices, obj1_uvs, obj1_normals);
GLuint BoxTexture;


std::string readShaderSource(const std::string& fileName)
{
	std::ifstream file(fileName.c_str());
	if (file.fail()) {
		std::cerr << "Error loading shader called " << fileName << std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();

	return stream.str();
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
	GLuint ShaderObj = glCreateShader(ShaderType);
	if (ShaderObj == 0) {
		std::cerr << "Error creating shader type " << ShaderType << std::endl;
		exit(EXIT_FAILURE);
	}

	/* bind shader source code to shader object */
	std::string outShader = readShaderSource(pShaderText);
	const char* pShaderSource = outShader.c_str();
	glShaderSource(ShaderObj, 1, (const GLchar * *)& pShaderSource, NULL);

	/* compile the shader and check for errors */
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		std::cerr << "Error compiling shader type " << ShaderType << ": " << InfoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	glAttachShader(ShaderProgram, ShaderObj); /* attach compiled shader to shader programme */
}

GLuint CompileShaders(const char* pVShaderText, const char* pFShaderText)
{
	//Start the process of setting up our shaders by creating a program ID
	//Note: we will link all the shaders together into this ID
	GLuint ShaderProgramID = glCreateProgram();
	if (ShaderProgramID == 0) {
		std::cerr << "Error creating shader program" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create two shader objects, one for the vertex, and one for the fragment shader
	AddShader(ShaderProgramID, pVShaderText, GL_VERTEX_SHADER);
	AddShader(ShaderProgramID, pFShaderText, GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };


	// After compiling all shader objects and attaching them to the program, we can finally link it
	glLinkProgram(ShaderProgramID);
	// check for program related errors using glGetProgramiv
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		std::cerr << "Error linking shader program: " << ErrorLog << std::endl;
		exit(EXIT_FAILURE);
	}

	// program has been successfully linked but needs to be validated to check whether the program can execute given the current pipeline state
	glValidateProgram(ShaderProgramID);
	// check for program related errors using glGetProgramiv
	glGetProgramiv(ShaderProgramID, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgramID, sizeof(ErrorLog), NULL, ErrorLog);
		std::cerr << "Invalid shader program: " << ErrorLog << std::endl;
		exit(EXIT_FAILURE);
	}
	return ShaderProgramID;
}


bool LoadCubeMapSide(GLuint texture, GLenum sideTarget, const char* fileName) {

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int forceChannels = 4;
	unsigned char* image_data = stbi_load(fileName, &x, &y, &n, 0); //stbi_load(fileName, &x, &y, &n, forceChannels);

	if (!image_data) {
		std::cerr << "Error: could not load " << fileName << std::endl;
		return false;
	}

	glTexImage2D(sideTarget, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data); // glTexImage2D(sideTarget, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	free(image_data);
	return true;
}



void CreateCubeMap(const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* texCube) {

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, texCube);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, *texCube);


	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	LoadCubeMapSide(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void computeTangentBasis() {

	for (unsigned int i = 0; i < obj1_vertices.size(); i += 3) {

		// Shortcuts for vertices
		glm::vec3& v0 = obj1_vertices[i + 0];
		glm::vec3& v1 = obj1_vertices[i + 1];
		glm::vec3& v2 = obj1_vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2& uv0 = obj1_uvs[i + 0];
		glm::vec2& uv1 = obj1_uvs[i + 1];
		glm::vec2& uv2 = obj1_uvs[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		obj1_tangents.push_back(tangent);
		obj1_tangents.push_back(tangent);
		obj1_tangents.push_back(tangent);

		// Same thing for binormals
		obj1_bitangents.push_back(bitangent);
		obj1_bitangents.push_back(bitangent);
		obj1_bitangents.push_back(bitangent);

	}

	// See "Going Further"
	for (unsigned int i = 0; i < obj1_vertices.size(); i += 1)
	{
		glm::vec3& n = obj1_normals[i];
		glm::vec3& t = obj1_tangents[i];
		glm::vec3& b = obj1_bitangents[i];

		// Gram-Schmidt orthogonalize
		t = glm::normalize(t - n * glm::dot(n, t));

		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f) {
			t = t * -1.0f;
		}

	}
}

void generateObjectBuffer(GLuint temp)
{
	GLuint vp_vbo = 0;

	objectloc1 = glGetAttribLocation(temp, "vertex_position");
	objectloc2 = glGetAttribLocation(temp, "vertex_normals");
	objectloc3 = glGetAttribLocation(temp, "vertex_uv");
	objectloc4 = glGetAttribLocation(temp, "vertex_tangent");
	objectloc5 = glGetAttribLocation(temp, "vertex_bitangent");

	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, cube_vertex_count * sizeof(glm::vec3), &obj1_vertices[0], GL_STATIC_DRAW);

	GLuint vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, cube_vertex_count * sizeof(glm::vec3), &obj1_normals[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, cube_vertex_count * sizeof(glm::vec2), &obj1_uvs[0], GL_STATIC_DRAW);

	GLuint tangentbuffer;
	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, obj1_vertices.size() * sizeof(glm::vec3), &obj1_tangents[0], GL_STATIC_DRAW);

	GLuint bitangentbuffer;
	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, obj1_vertices.size() * sizeof(glm::vec3), &obj1_bitangents[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glEnableVertexAttribArray(objectloc1);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(objectloc1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(objectloc2);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(objectloc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(objectloc3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(objectloc3, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(objectloc4);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glVertexAttribPointer(objectloc4, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(objectloc5);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glVertexAttribPointer(objectloc5, 3, GL_FLOAT, GL_FALSE, 0, NULL);

}



void init(void) {


	// Cube Map
	glGenBuffers(1, &skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); //3 * sizeof(float)

	// Cube Map
	SkyBoxShaderProgramID = CompileShaders("C:/Users/lenovo/source/repos/Rendering Assignment-4/Shaders/sbVS.txt",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Shaders/sbFS.txt");
	generateObjectBuffer(SkyBoxShaderProgramID);

	// Mapping Shader
	ShaderProgramID = CompileShaders("C:/Users/lenovo/source/repos/Rendering Assignment-4/Shaders/objectVS.txt",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Shaders/objectFS.txt");
	generateObjectBuffer(ShaderProgramID);

	CreateCubeMap("C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/negz.jpg",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/posz.jpg",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/posy.jpg",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/negy.jpg",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/negx.jpg",
		"C:/Users/lenovo/source/repos/Rendering Assignment-4/Skybox/learnopengl/posx.jpg", &textureID);

}


GLuint TextureFromFile(const char* path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps

	int width, height, nrChannels;

	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 1) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			fprintf(stderr, "Error: Unexpected image format.\n");
			exit(EXIT_FAILURE);
		}
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	std::cout << "loaded texture" << std::endl;
	return texture;

}

void display(void) {

	// Cube Map
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glClearColor(0.5f, 0.5f, 0.5f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthFunc(GL_LEQUAL);
	glUseProgram(SkyBoxShaderProgramID);
	glActiveTexture(GL_TEXTURE0);

	int matrix_location = glGetUniformLocation(SkyBoxShaderProgramID, "model");
	int view_mat_location = glGetUniformLocation(SkyBoxShaderProgramID, "view");
	int proj_mat_location = glGetUniformLocation(SkyBoxShaderProgramID, "proj");

	mat4 view = look_at(vec3(0.0f, 0.0f, 0.0f), vec3(0.1, 0.0, 0.1), vec3(0.0, 1.0, 0.0));
	mat4 persp_proj = perspective(90.0, width / height, 0.01, 10.0);

	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view.m);
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, persp_proj.m);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, skyboxVertexCount);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);

	// Cube
	glUseProgram(ShaderProgramID);

	if (imageLoadFlag == 0) {
		BoxTexture = TextureFromFile("image/steel.jpg");
		imageLoadFlag++;
	}

	GLuint TextureID = glGetUniformLocation(ShaderProgramID, "TextureSampler");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BoxTexture);
	glUniform1i(TextureID, 0);


	int shader_matrix_location = glGetUniformLocation(ShaderProgramID, "model");
	int shader_view_mat_location = glGetUniformLocation(ShaderProgramID, "view");
	int shader_proj_mat_location = glGetUniformLocation(ShaderProgramID, "proj");
	GLuint ModelViewProj = glGetUniformLocation(ShaderProgramID, "MVP");

	mat4 shader_persp_proj = perspective(objSize, (float)width / (float)height, 0.5, 50.0);
	glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1, 0.0, 0.1), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(2.55, 0.1, 1.4));
	ModelMatrix = glm::rotate(ModelMatrix, rotateAnglex, glm::vec3(1, 0, 0));
	ModelMatrix = glm::rotate(ModelMatrix, rotateAngley, glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, rotateAnglez, glm::vec3(0, 0, 1));
	glm::mat4 ProjMatrix = glm::perspective(objSize, (float)(width) / (float)height, 0.5f, 50.0f);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
	glm::mat4 MVP = ProjMatrix * ViewMatrix * ModelMatrix;

	glUniformMatrix4fv(shader_proj_mat_location, 1, GL_FALSE, &ProjMatrix[0][0]);
	glUniformMatrix4fv(shader_view_mat_location, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(shader_matrix_location, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ModelViewProj, 1, GL_FALSE, &MVP[0][0]);
	glBindVertexArray(objectVAO);
	glDrawArrays(GL_TRIANGLES, 0, cube_vertex_count);
	glBindVertexArray(0);

	glutSwapBuffers();
}



void keyPress(unsigned char key, int xmouse, int ymouse) {
	switch (key) {
	case('q'):
		objSize += 2;
		std::cout << objSize << "objSize" << std::endl;
		break;
	case('a'):
		objSize -= 2;
		std::cout << objSize << "objSize" << std::endl;
		break;
	case ('w'):
		rotateAnglex += 0.5;
		std::cout << rotateAnglex << "Keypress: " << key << std::endl;
		break;
	case ('s'):
		rotateAnglex -= 0.5;
		std::cout << rotateAnglex << "Keypress: " << key << std::endl;
		break;
	case ('e'):
		rotateAngley += 0.5;
		std::cout << rotateAngley << "Keypress: " << key << std::endl;
		break;
	case ('d'):
		rotateAngley -= 0.5;
		std::cout << rotateAngley << "Keypress: " << key << std::endl;
		break;
	case ('r'):
		rotateAnglez += 0.5;
		std::cout << rotateAnglez << "Keypress: " << key << std::endl;
		break;
	case ('f'):
		rotateAnglez -= 0.5;
		std::cout << rotateAnglez << "Keypress: " << key << std::endl;
		break;
	}
};


//not sure i need this
void updateScene() {

	// Wait until at least 16ms passed since start of last frame (Effectively caps framerate at ~60fps)
	static DWORD  last_time = 0;
	DWORD  curr_time = timeGetTime();
	float  delta = (curr_time - last_time) * 0.001f;
	if (delta > 0.03f)
		delta = 0.03f;
	last_time = curr_time;

	// For Rotation
	rotatez += 0.1f;
	//std::cout << rotatez << std::endl;
	// Draw the next frame
	glutPostRedisplay();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(argv[1]);
	computeTangentBasis();

	/* register call back functions */
	glutDisplayFunc(display);

	glutIdleFunc(updateScene);
	glutKeyboardFunc(keyPress);

	glewExperimental = GL_TRUE; //not sure point of this?
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(res) << std::endl;
		return EXIT_FAILURE;
	}

	init();
	glutMainLoop();
	return 0;
}