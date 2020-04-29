#include "loader.h"

LoadObj::LoadObj(std::string filename,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals) {
	std::ifstream ifs(filename.c_str(), std::ifstream::in);
	std::string line, key;
	while (ifs.good() && !ifs.eof() && std::getline(ifs, line)) {
		key = "";
		std::stringstream stringstream(line);
		stringstream >> key >> std::ws;

		if (key == "v") { // vertex
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			vertices.push_back(v);
		}
		else if (key == "vp") { // parameter
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			parameters.push_back(v);
		}
		else if (key == "vt") { // texture coordinate
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			texcoords.push_back(v);
		}
		else if (key == "vn") { // normal
			vertex v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.v.push_back(x);
			}
			v.normalize();
			normals.push_back(v);
		}
		else if (key == "f") { // face
			face f; int v, t, n;
			while (!stringstream.eof()) {
				stringstream >> v >> std::ws;
				f.vertex.push_back(v - 1);
				if (stringstream.peek() == '/') {
					stringstream.get();
					if (stringstream.peek() == '/') {
						stringstream.get();
						stringstream >> n >> std::ws;
						f.normal.push_back(n - 1);
					}
					else {
						stringstream >> t >> std::ws;
						f.texture.push_back(t - 1);
						if (stringstream.peek() == '/') {
							stringstream.get();
							stringstream >> n >> std::ws;
							f.normal.push_back(n - 1);
						}
					}
				}
			}
			faces.push_back(f);
		}
		else {

		}
	}
	ifs.close();
	std::cout << "\n-------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Name: " << filename << std::endl;
	std::cout << "Vertices: " << vertices.size() << std::endl;
	std::cout << "Parameters: " << parameters.size() << std::endl;
	std::cout << "Texture Coordinates: " << texcoords.size() << std::endl;
	std::cout << "Normals: " << normals.size() << std::endl;
	std::cout << "Faces: " << faces.size() << std::endl << std::endl;

	for (int facesIndex = 0; facesIndex < faces.size(); facesIndex++) {
		for (int vertex_index = 0; vertex_index < faces[facesIndex].vertex.size(); vertex_index++) {
			floatVertices.push_back(vertices[faces[facesIndex].vertex[vertex_index]].v[0]);
			floatVertices.push_back(vertices[faces[facesIndex].vertex[vertex_index]].v[1]);
			floatVertices.push_back(vertices[faces[facesIndex].vertex[vertex_index]].v[2]);
		}
		for (int textureIndex = 0; textureIndex < faces[textureIndex].texture.size(); textureIndex++) {
			floatTex.push_back(texcoords[faces[facesIndex].texture[textureIndex]].v[0]);
			floatTex.push_back(texcoords[faces[facesIndex].texture[textureIndex]].v[1]);
		}
		for (int normalIndex = 0; normalIndex < faces[normalIndex].normal.size(); normalIndex++) {
			floatNormals.push_back(normals[faces[facesIndex].normal[normalIndex]].v[0]);
			floatNormals.push_back(normals[faces[facesIndex].normal[normalIndex]].v[1]);
			floatNormals.push_back(normals[faces[facesIndex].normal[normalIndex]].v[2]);
		}
	}
	numvertices = floatVertices.size() / 3;
	std::cout << "numvertices" << numvertices << std::endl;
	std::cout << "Face Vertices: " << floatVertices.size() << std::endl;
	std::cout << "Face Textures: " << floatTex.size() << std::endl;
	std::cout << "Face Normals: " << floatNormals.size() << std::endl;
	// Condition to get texture
	if (faces.size() > texcoords.size()) {
		for (int i = 0; i < faces.size(); i++) {
			// Get the attributes thanks to the index
			glm::vec3 v3_vertex = glm::vec3(faces[i].vertex[0], faces[i].vertex[1], faces[i].vertex[2]);
			glm::vec3 v3_normal = glm::vec3(faces[i].normal[0], faces[i].normal[1], faces[i].normal[2]);

			// Put the attributes in buffers
			out_vertices.push_back(v3_vertex);
			out_normals.push_back(v3_normal);
		}
		for (int i = 0; i < texcoords.size(); i++) {
			glm::vec2 v2_uv = glm::vec2(faces[i].texture[0], faces[i].texture[1]);
			out_uvs.push_back(v2_uv);
		}

	}
	else {
		for (int i = 0; i < faces.size(); i++) {
			// Get the attributes thanks to the index
			glm::vec3 v3_vertex = glm::vec3(faces[i].vertex[0], faces[i].vertex[1], faces[i].vertex[2]);
			glm::vec2 v2_uv = glm::vec2(faces[i].texture[0], faces[i].texture[1]);
			glm::vec3 v3_normal = glm::vec3(faces[i].normal[0], faces[i].normal[1], faces[i].normal[2]);

			// Put the attributes in buffers
			out_vertices.push_back(v3_vertex);
			out_uvs.push_back(v2_uv);
			out_normals.push_back(v3_normal);
		}

	}
	vertices.clear();
	texcoords.clear();
	normals.clear();
	faces.clear();
}

float* LoadObj::getVertices() {
	return floatVertices.data();
}

float* LoadObj::getNormals() {
	return floatNormals.data();
}

float* LoadObj::getTexcoords() {
	return floatTex.data();
}

int LoadObj::getNumVertices() {
	return numvertices;
}