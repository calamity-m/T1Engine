#include "MeshLoader.h"
#include <vector>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

MeshLoader::MeshLoader() {

}


std::vector<MeshLoader::Mesh> MeshLoader::loadTexturedMeshes(char * fname)
{
	// Buffer for every single line
	std::vector<Vertex*> vertices;
	std::vector<Vertex*> normals;
	std::vector<Vertex*> uvs;
	std::vector<MeshRaw*> meshes;

	std::ifstream in(fname);

	float curTime = glutGet(GLUT_ELAPSED_TIME);

	if (!in.is_open()) {
		printf("Error loading file\n");
		return std::vector<Mesh>();
	}

	char buffer[256];

	meshes.push_back(new MeshRaw("Base"));

	// store our buffer
	while (!in.eof()) {
		in.getline(buffer, 256);

		const char *str = buffer;

		if (str[0] == '#') {
			continue;
		}
		else if (str[0] == 'v') {
			// We have an x y z coordinate
			if (str[1] == ' ') {
				// We have a vertex
				float tempx, tempy, tempz;
				sscanf(str, "v %f %f %f", &tempx, &tempy, &tempz);
				vertices.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (str[1] == 'n') {
				// We have a vertex normal
				float tempx, tempy, tempz;
				sscanf(str, "vn %f %f %f", &tempx, &tempy, &tempz);
				normals.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (str[1] == 't') {
				// We have a vertex texture coordinate
				float tempx, tempy;
				sscanf(str, "vt %f %f", &tempx, &tempy);
				uvs.push_back(new  Vertex(tempx, tempy, 0));
			}
		}
		else if (str[0] == 'g') {
			// We have a group
			std::string n(str);

			try {
				n.erase(0, 2);
				meshes.push_back(new MeshRaw(str));
			}
			catch (std::out_of_range) {
				meshes.push_back(new MeshRaw("unamed"));
			}
		}
		else if (str[0] == 'f')
		{
			// We have a face
			int v1, v2, v3, v4;
			int n1, n2, n3, n4;

			std::string l(str);

			int p = count(l.begin(), l.end(), '/');

			/* WE ARE HANDLING TRIANGLE FACES */
			if (p == 0 || p == 3 || p == 6) {
				// We have a triangle
				// if (p == 6) {
				if (l.find("//") != std::string::npos) {
					// We found an //
					sscanf(l.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, n1, n2, n3));
				}
				else if (l.find("/") != std::string::npos) {
					// we found only a /
					int t[3];
					sscanf(l.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, n1, n2, n3, t[0], t[1], t[2]));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(l.c_str(), "f %d %d %d", &v1, &v2, &v3);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, 0, 0, 0));
				}
			} /* NOW HANDLING QUAD FACES */
			else {
				// We have a quad
				if (l.find("//") != std::string::npos) {
					// We found an //
					sscanf(l.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, v4, n1, n2, n3, n4));
				}
				else if (l.find("/") != std::string::npos) {
					int t[4];
					sscanf(l.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3, &v4, &t[3], &n4);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, v4, n1, n2, n3, n4, t[0], t[1], t[2], t[3]));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(l.c_str(), "f %d %d %d %d", &v1, &v2, &v3, &v4);
					meshes[meshes.size() - 1]->addFace(Face(v1, v2, v3, v4, 0, 0, 0, 0));
				}
			}
		}

		//delete str;
	}

	int x;
	x = glGenLists(meshes.size());

	int currList = x;

	std::vector<Mesh> finalMeshes;

	float oldTime = glutGet(GLUT_ELAPSED_TIME);
	float showTime = oldTime - curTime;
	printf("Read Mesh: %.2fms\n", showTime);
	curTime = oldTime;

	for (int i = 0; i < meshes.size(); i++) {
		MeshRaw m = *meshes[i];
		glNewList(++currList, GL_COMPILE);
		//finalMeshes.push_back(Mesh(m.name, currList, Vertex()));
		float x, y, z;
		x = y = z = 0;
		int count = 0;

		for (int j = 0; j < m.face.size(); j++) {
			if (m.getFace(j).quad) {
				for (int k = 0; k < 4; k++) {
					x += vertices[m.getFace(j).vertexIndex[k] - 1]->x;
					y += vertices[m.getFace(j).vertexIndex[k] - 1]->y;
					z += vertices[m.getFace(j).vertexIndex[k] - 1]->z;
					count++;
				}
			}
			else {
				for (int k = 0; k < 3; k++) {
					x += vertices[m.getFace(j).vertexIndex[k] - 1]->x;
					y += vertices[m.getFace(j).vertexIndex[k] - 1]->y;
					z += vertices[m.getFace(j).vertexIndex[k] - 1]->z;
					count++;
				}
			}
		}

		finalMeshes.push_back(Mesh(m.name, currList, Vertex(x /= count, y /= count, z /= count)));
		/****** Possibly optomise by storing  quads and triangles in different vectors ******/
		for (int j = 0; j < m.face.size(); j++) {

			if (m.getFace(j).quad) {
				glBegin(GL_QUADS);

				for (int k = 0; k < 4; k++) {
					if (normals.size() > 0)
						glNormal3f(normals[m.getFace(j).normalIndex[k] - 1]->x, normals[m.getFace(j).normalIndex[k] - 1]->y, normals[m.getFace(j).normalIndex[k] - 1]->z);

					if (m.getFace(j).textured)
						glTexCoord2f(uvs[m.getFace(j).uvIndex[k] -1]->x, uvs[m.getFace(j).uvIndex[k] - 1]->y);

					glVertex3f(vertices[m.getFace(j).vertexIndex[k] - 1]->x, vertices[m.getFace(j).vertexIndex[k] - 1]->y, vertices[m.getFace(j).vertexIndex[k] - 1]->z);
				}
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);

				for (int k = 0; k < 3; k++) {
					if (normals.size() > 0)
						glNormal3f(normals[m.getFace(j).normalIndex[k] - 1]->x, normals[m.getFace(j).normalIndex[k] - 1]->y, normals[m.getFace(j).normalIndex[k] - 1]->z);

					if (m.getFace(j).textured)
						glTexCoord2f(uvs[m.getFace(j).uvIndex[k] - 1]->x, uvs[m.getFace(j).uvIndex[k] - 1]->y);

					glVertex3f(vertices[m.getFace(j).vertexIndex[k] - 1]->x, vertices[m.getFace(j).vertexIndex[k] - 1]->y, vertices[m.getFace(j).vertexIndex[k] - 1]->z);
				}
				glEnd();
			}
		}

		glEndList();
	}

	oldTime = glutGet(GLUT_ELAPSED_TIME);
	printf("Loaded Mesh: %.2fms\n", oldTime - curTime);
	
	printf("Number of Vertices: %d\nNumber of Normals: %d\n", vertices.size(), normals.size());

	/*
	int count = 0;
	for (int i = 0; i < meshes.size(); i++) {
		for (int j = 0; j < meshes[i]->face.size(); j++) {
			count++;
		}
	}

	printf("Number of Total Faces: %d\n", count);
	*/

	for (int i = 0; i<vertices.size(); i++)
		delete vertices[i];
	for (int i = 0; i<normals.size(); i++)
		delete normals[i];
	for (int i = 0; i < meshes.size(); i++) {
		//delete meshes[i]->getFace
		delete meshes[i];
	}
	for (int i = 0; i < uvs.size(); i++)
		delete uvs[i];

	return finalMeshes;
}


std::vector<MeshLoader::Mesh> MeshLoader::loadMeshes(char * fname) {
	// Buffer for every single line
	std::vector<Vertex*> vertices;
	std::vector<Vertex*> normals;	
	std::vector<MeshRaw*> meshes;

	std::ifstream in(fname);

	float curTime = glutGet(GLUT_ELAPSED_TIME);

	if (!in.is_open()) {
		printf("Error loading file\n");
		return std::vector<Mesh>();
	}

	char buffer[256];

	meshes.push_back(new MeshRaw("Base"));

	// store our buffer
	while (!in.eof()) {
		in.getline(buffer, 256);

		const char *str = buffer;

		if (str[0] == '#') {
			continue;
		}
		else if (str[0] == 'v') {
			// We have an x y z coordinate
			if (str[1] == ' ') {
				// We have a vertex
				float tempx, tempy, tempz;
				sscanf(str, "v %f %f %f", &tempx, &tempy, &tempz);
				vertices.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (str[1] == 'n') {
				// We have a vertex normal
				float tempx, tempy, tempz;
				sscanf(str, "vn %f %f %f", &tempx, &tempy, &tempz);
				normals.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (str[1] == 't') {
				// We have a vertex texture coordinate
			}
		}
		else if (str[0] == 'g') {
			// We have a group
			std::string n(str);

			try {
				n.erase(0, 2);
				meshes.push_back(new MeshRaw(str));
			}
			catch (std::out_of_range) {
				meshes.push_back(new MeshRaw("unamed"));
			}
		}
		else if (str[0] == 'f')
		{
			// We have a face
			int v1, v2, v3, v4;
			int n1, n2, n3, n4;

			std::string l(str);

			int p = count(l.begin(), l.end(), '/');

			/* WE ARE HANDLING TRIANGLE FACES */
			if (p == 0 || p == 3 || p == 6) {
				// We have a triangle
				// if (p == 6) {
				if (l.find("//") != std::string::npos) {
					// We found an //
					sscanf(l.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
					meshes[meshes.size()-1]->addFace(*new Face(v1, v2, v3, n1, n2, n3));
				}
				else if (l.find("/") != std::string::npos) {
					// we found only a /
					int t[3];
					sscanf(l.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3);
					meshes[meshes.size() - 1]->addFace(*new Face(v1, v2, v3, n1, n2, n3));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(l.c_str(), "f %d %d %d", &v1, &v2, &v3);
					meshes[meshes.size() - 1]->addFace(*new Face(v1, v2, v3, 0, 0, 0));
				}
			} /* NOW HANDLING QUAD FACES */
			else {
				// We have a quad
				if (l.find("//") != std::string::npos) {
					// We found an //
					sscanf(l.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4);
					meshes[meshes.size() - 1]->addFace(*new Face(v1, v2, v3, v4, n1, n2, n3, n4));
				}
				else if (l.find("/") != std::string::npos) {
					int t[4];
					sscanf(l.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3, &v4, &t[3], &n4);
					meshes[meshes.size() - 1]->addFace(*new Face(v1, v2, v3, v4, n1, n2, n3, n4));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(l.c_str(), "f %d %d %d %d", &v1, &v2, &v3, &v4);
					meshes[meshes.size() - 1]->addFace(*new Face(v1, v2, v3, v4, 0, 0, 0, 0));
				}
			}
		}

		//delete str;
	}

	int x;
	x = glGenLists(meshes.size());

	int currList = x;

	std::vector<Mesh> finalMeshes;

	float oldTime = glutGet(GLUT_ELAPSED_TIME);
	float showTime = oldTime - curTime;
	printf("Read Mesh: %.2fms\n", showTime);
	curTime = oldTime;

	for (int i = 0; i < meshes.size(); i++) {
		MeshRaw m = *meshes[i];
		glNewList(++currList, GL_COMPILE);
		//finalMeshes.push_back(Mesh(m.name, currList, Vertex()));
		float x, y, z;
		x = y = z = 0;
		int count = 0;

		for (int j = 0; j < m.face.size(); j++) {
			if (m.getFace(j).quad) {
				for (int k = 0; k < 4; k++) {
					x += vertices[m.getFace(j).vertexIndex[k] - 1]->x;
					y += vertices[m.getFace(j).vertexIndex[k] - 1]->y;
					z += vertices[m.getFace(j).vertexIndex[k] - 1]->z;
					count++;
				}
			}
			else {
				for (int k = 0; k < 3; k++) {
					x += vertices[m.getFace(j).vertexIndex[k] - 1]->x;
					y += vertices[m.getFace(j).vertexIndex[k] - 1]->y;
					z += vertices[m.getFace(j).vertexIndex[k] - 1]->z;
					count++;
				}
			}
		}

		finalMeshes.push_back(Mesh(m.name, currList, Vertex(x /= count, y /= count, z /= count)));
		/****** Possibly optomise by storing  quads and triangles in different vectors ******/
		for (int j = 0; j < m.face.size(); j++) {

			if (m.getFace(j).quad) {
				glBegin(GL_QUADS);
				
				for (int k = 0; k < 4; k++) {
					if (normals.size() > 0)
						glNormal3f(normals[m.getFace(j).normalIndex[k] - 1]->x, normals[m.getFace(j).normalIndex[k] - 1]->y, normals[m.getFace(j).normalIndex[k] - 1]->z);

					glVertex3f(vertices[m.getFace(j).vertexIndex[k] - 1]->x, vertices[m.getFace(j).vertexIndex[k] - 1]->y, vertices[m.getFace(j).vertexIndex[k] - 1]->z);
				}
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
				
				for (int k = 0; k < 3; k++) {
					if (normals.size() > 0)
						glNormal3f(normals[m.getFace(j).normalIndex[k] - 1]->x, normals[m.getFace(j).normalIndex[k] - 1]->y, normals[m.getFace(j).normalIndex[k] - 1]->z);

					glVertex3f(vertices[m.getFace(j).vertexIndex[k] - 1]->x, vertices[m.getFace(j).vertexIndex[k] - 1]->y, vertices[m.getFace(j).vertexIndex[k] - 1]->z);
				}
				glEnd();
			}
		}

		glEndList();
	}

	oldTime = glutGet(GLUT_ELAPSED_TIME);
	printf("Loaded Mesh: %.2fms\n", oldTime - curTime);

	printf("Number of Vertices: %d\nNumber of Normals: %d\n", vertices.size(), normals.size());

	for (int i = 0; i<vertices.size(); i++)
		delete vertices[i];
	for (int i = 0; i<normals.size(); i++)
		delete normals[i];
	for (int i = 0; i<meshes.size(); i++)
		delete meshes[i];

	return finalMeshes;
}

int MeshLoader::loadMesh(char * fname) {
	// Buffer for every single line
	std::vector<std::string*> lines;
	std::vector<Vertex*> vertices;
	std::vector<Face*> modelFaces;
	std::vector<Vertex*> normals;

	std::ifstream in(fname);

	if (!in.is_open()) {
		printf("Error loading file\n");
		return -1;
	}

	char buffer[256];

	/* optimise to only read through once */
	// store our buffer
	while (!in.eof()) {
		in.getline(buffer, 256);

		std::string line(buffer);

		if (line.c_str()[0] == '#') {
			continue;
		}
		else if (line.c_str()[0] == 'v') {
			// We have an x y z coordinate
			if (line.c_str()[1] == ' ') {
				// We have a vertex
				float tempx, tempy, tempz;
				sscanf(line.c_str(), "v %f %f %f", &tempx, &tempy, &tempz);
				vertices.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (line.c_str()[1] == 'n') {
				// We have a vertex normal
				float tempx, tempy, tempz;
				sscanf(line.c_str(), "vn %f %f %f", &tempx, &tempy, &tempz);
				normals.push_back(new Vertex(tempx, tempy, tempz));
			}
			else if (line.c_str()[1] == 't') {
				// We have a vertex texture coordinate
			}
		}
		else if (line.c_str()[0] == 'g') {

		}
		else if (line.c_str()[0] == 'f')
		{
			// We have a face
			int v1, v2, v3, v4;
			int n1, n2, n3, n4;

			int p = count(line.begin(), line.end(), '/');

			/* WE ARE HANDLING TRIANGLE FACES */
			if (p == 0 || p == 3 || p == 6) {
				// We have a triangle
				if (line.find("//") != std::string::npos) {
					// We found an //
					sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3);
					modelFaces.push_back(new Face(v1, v2, v3, n1, n2, n3));
				}
				else if (line.find("/") != std::string::npos) {
					// we found only a /
					int t[3];
					sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3);
					modelFaces.push_back(new Face(v1, v2, v3, n1, n2, n3));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(line.c_str(), "f %d %d %d", &v1, &v2, &v3);
					modelFaces.push_back(new Face(v1, v2, v3, 0, 0, 0));
				}
			} /* NOW HANDLING QUAD FACES */
			else {
				// We have a quad
				if (line.find("//") != std::string::npos) {
					// We found an //
					sscanf(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4);
					modelFaces.push_back(new Face(v1, v2, v3, v4, n1, n2, n3, n4));
				}
				else if (line.find("/") != std::string::npos) {
					int t[4];
					sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t[0], &n1, &v2, &t[1], &n2, &v3, &t[2], &n3, &v4, &t[3], &n4);
					modelFaces.push_back(new Face(v1, v2, v3, v4, n1, n2, n3, n4));
				}
				else {
					// We have a basic triangulated mesh without normals specified
					sscanf(line.c_str(), "f %d %d %d %d", &v1, &v2, &v3, &v4);
					modelFaces.push_back(new Face(v1, v2, v3, v4, 0, 0, 0, 0));
				}
			}
		}
	}

	// Generate a list and store its ID
	int id;	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	// Create our model in our new list
	for (int i = 0; i < modelFaces.size(); i++) {
		// Check if we're creating a quad face or a triangle
		if (modelFaces[i]->quad) {
			glBegin(GL_QUADS);
			// Only draw normals if we have them specified
			for (int k = 0; k < 4; k++) {
				if (normals.size() > 0)
					glNormal3f(normals[modelFaces[i]->normalIndex[k] - 1]->x, normals[modelFaces[i]->normalIndex[k] - 1]->y, normals[modelFaces[i]->normalIndex[k] - 1]->z);

				glVertex3f(vertices[modelFaces[i]->vertexIndex[k] - 1]->x, vertices[modelFaces[i]->vertexIndex[k] - 1]->y, vertices[modelFaces[i]->vertexIndex[k] - 1]->z);
			}
			glEnd();
		}
		else {
			glBegin(GL_TRIANGLES);
			// Only draw normals if we have them specified
			for (int k = 0; k < 3; k++) {
				if (normals.size() > 0)
					glNormal3f(normals[modelFaces[i]->normalIndex[k] - 1]->x, normals[modelFaces[i]->normalIndex[k] - 1]->y, normals[modelFaces[i]->normalIndex[k] - 1]->z);

				glVertex3f(vertices[modelFaces[i]->vertexIndex[k] - 1]->x, vertices[modelFaces[i]->vertexIndex[k] - 1]->y, vertices[modelFaces[i]->vertexIndex[k] - 1]->z);
			}
			glEnd();
		}
	}
	// End our list
	glEndList();

	// Return our list ID for later use now that we have fully loaded model
	return id;
}
