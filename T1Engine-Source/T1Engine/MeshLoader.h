#ifndef meshloader_h
#define meshloader_h

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "glut.h"

/*
Based off of the following (full referencing provided in report)
https://stackoverflow.com/questions/14887012/object-loader-in-opengl/14887071#14887071
https://www.youtube.com/watch?v=rF9Tud6E1yI
https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html
https://www.youtube.com/watch?v=H2pjr6xtG9M&index=15&list=PL0AB023E769342AFE&t=3s
http://nehe.gamedev.net/tutorial/display_lists/15003/
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
http://netization.blogspot.com.au/2014/10/loading-obj-files-in-opengl.html
http://3dviewer.net/ (helps in having another source to check validity of how I loaded my models)
*/
class MeshLoader {

public:

	struct Vertex {
		// XYZ Coordinates
		float x, y, z;
		// Vertex Constructor
		Vertex(float xc, float yc, float zc) {
			x = xc;
			y = yc;
			z = zc;
		};
		Vertex() {
			x = 0;
			y = 0;
			z = 0;
		}

	};

	struct Face {
		bool quad;
		bool textured;
		/* Change this so that we can store more normals */
		int normalIndex[4];
		int vertexIndex[4];
		int uvIndex[4];

		Face(int v1, int v2, int v3, int n1, int n2, int n3) {
			vertexIndex[0] = v1;
			vertexIndex[1] = v2;
			vertexIndex[2] = v3;
			normalIndex[0] = n1;
			normalIndex[1] = n2;
			normalIndex[2] = n3;
			uvIndex[0] = 0;
			uvIndex[1] = 0;
			uvIndex[2] = 0;
			textured = false;
			quad = false;
		}

		Face(int v1, int v2, int v3, int v4, int n1, int n2, int n3, int n4) { //overloaded constructor for quad
			vertexIndex[0] = v1;
			vertexIndex[1] = v2;
			vertexIndex[2] = v3;
			vertexIndex[3] = v4;
			normalIndex[0] = n1;
			normalIndex[1] = n2;
			normalIndex[2] = n3;	
			normalIndex[3] = n4;
			uvIndex[0] = 0;
			uvIndex[1] = 0;
			uvIndex[2] = 0;
			uvIndex[3] = 0;
			textured = false;
			quad = true;
		}

		Face(int v1, int v2, int v3, int n1, int n2, int n3, int uv1, int uv2, int uv3) {
			vertexIndex[0] = v1;
			vertexIndex[1] = v2;
			vertexIndex[2] = v3;
			normalIndex[0] = n1;
			normalIndex[1] = n2;
			normalIndex[2] = n3;
			uvIndex[0] = uv1;
			uvIndex[1] = uv2;
			uvIndex[2] = uv3;
			textured = true;
			quad = false;
		}

		Face(int v1, int v2, int v3, int v4, int n1, int n2, int n3, int n4, int uv1, int uv2, int uv3, int uv4) { //overloaded constructor for quad
			vertexIndex[0] = v1;
			vertexIndex[1] = v2;
			vertexIndex[2] = v3;
			vertexIndex[3] = v4;
			normalIndex[0] = n1;
			normalIndex[1] = n2;
			normalIndex[2] = n3;
			normalIndex[3] = n4;
			uvIndex[0] = uv1;
			uvIndex[1] = uv2;
			uvIndex[2] = uv3;
			uvIndex[3] = uv4;
			textured = true;
			quad = true;
		}

	};

	struct MeshRaw {
		std::string name;
		std::vector<Face> face;

		MeshRaw(std::string mName) {
			name = mName;
		}

		void addFace(Face f) {
			face.push_back(f);
		}

		Face getFace(int i) {
			return face[i];
		}

	};

	struct Mesh {

		Vertex pos;
		std::string name;
		int id;
		//Vertex xyz;

		Mesh(std::string meshName, int meshId, Vertex position) {
			name = meshName;
			id = meshId;
			pos = position;
		}

	};

	MeshLoader();

	// load model as grouped mesh
	std::vector<Mesh> loadMeshes(char *fname);

	// load model as grouped mesh with applied uv coordinates
	std::vector<Mesh> loadTexturedMeshes(char *fname);

	// load model as single mesh
	int loadMesh(char *fname);

};

#endif // !meshdata_h
