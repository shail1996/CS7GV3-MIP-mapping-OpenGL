//reference: https://github.com/opengl-tutorials/ogl/blob/master/tutorial13_normal_mapping/NormalMapping.vertexshader
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normals;
layout(location = 3) in vec3 vertex_tangent;
layout(location = 4) in vec3 vertex_bitangent;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertex_position,1);
	
	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertex_position,1)).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertex_position,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// UV of the vertex. No special space for this one.
	UV = vertex_uv;
	
	// model to camera = ModelView
	vec3 vertexTangent_cameraspace = MV3x3 * vertex_tangent;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertex_bitangent;
	vec3 vertexNormal_cameraspace = MV3x3 * vertex_normals;
	
	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace	
	)); // You can use dot products instead of building this matrix and transposing it. See References for details.

	LightDirection_tangentspace = TBN * LightDirection_cameraspace;
	EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
	
	
}