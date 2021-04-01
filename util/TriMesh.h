#ifndef TRIMESH_H
#define TRIMESH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sstream>

#include "hittable_list.h"
#include "TriangleMesh.cpp"

using namespace std;

class TriMesh {
	public:
	TriMesh() {}
	TriMesh(char* name, vec3 kdi, vec3 ksi) {
		fileName = name;
		kd = kdi;
		ks = ksi;
	}

	/*	Loads an obj file
	*/
	void loadFromOBJ() {
		FILE* stream;
		size_t len = 0;
		ssize_t nread = 0;

		stream = fopen(fileName, "r");
		char* line = NULL;

		if (stream == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

		while ((nread = getline(&line, &len, stream)) != -1) {
			if (line[0] == '#') {
				continue;
			} else {
				//fwrite(line, nread, 1, stdout);
				if (line[0] == 'v') {
					stringstream ss(line);
					string m = line;
					int axis = 0;
					vec3 vec;
					while (getline(ss,m,' ')) {
						if (m[0] == 'v' || m[0] == '\n') continue;
						if (axis == 2) m[m.size()-1] = '\0';
						if (axis >= 4) break;
						//cout << "axis = " << axis << endl;
						//cout << "here = " << m << endl; // m might be \n
						vec[axis] = stod(m);
						axis += 1;
					}
					vertices.push_back(vec);
				} else if (line[0] == 'f') {
					stringstream ss(line);
					string m = line;
					int axis = 0;
					vec3 vec;
					while (getline(ss,m,' ')) {
						if (m[0] == 'f' || m[0] == '\n') continue;
						if (axis == 2) m[m.size()-1] = '\0';
						if (axis >= 4) break;
						//cout << "axis = " << axis << endl;
						//cout << "here = " << m << endl; // m might be \n
						vec[axis] = stoi(m);
						axis += 1;
					}
					faces.push_back(vec);
				} else {
					continue;
				}
			}
		}
		numVertices = vertices.size();
		numFaces = faces.size();

		for (int i = 0; i < numVertices; i++) {
			normals.push_back(vec3(0,0,0));
		}

		//cout << numVertices << endl;
		//cout << numFaces << endl;
		//printVertices();
		//printFaces();
	}

	/*	Generates the triangular mesh
	*	returns a hittable_list of triangles
	*/
	hittable_list generateTriangles() {
		// faces stores a vector of 3 vertices
		// vertices stores a vector of 3 doubles
		hittable_list triangles;
		for (int i = 0; i < numFaces; i++) {
			vec3 face = faces[i];
			int index1 = face[0];
			int index2 = face[1];
			int index3 = face[2];
	
			vec3 v1 = vertices[index1-1];
			vec3 v2 = vertices[index2-1];
			vec3 v3 = vertices[index3-1];

			/*v1 *= 200;
			v2 *= 200;
			v3 *= 200;
			*/
			v1 = uniformScale(v1, 50);
			v2 = uniformScale(v2, 50);
			v3 = uniformScale(v3, 50);
			/*v1 = rotateAboutPoint(v1, 90, 1);
			v2 = rotateAboutPoint(v2, 90, 1);
			v3 = rotateAboutPoint(v3, 90, 1);*/
			triangles.add(make_shared<TriangleMesh>(v1, v2, v3, kd, ks, index1, index2, index3));

			vec3 per_face_normal = cross(v2-v1, v3-v1);
			//per_face_normal = normalize(per_face_normal);
	
			normals[index1-1] += per_face_normal;
			normals[index2-1] += per_face_normal;
			normals[index3-1] += per_face_normal;
		}

		for (int i = 0; i < normals.size(); i++) {
			normals[i] = normalize(normals[i]);
		}
		/*normals[0] = vec3(1,0,0);
		normals[1] = vec3(0,1,0);
		normals[2] = vec3(0,0,1);*/
		//printNormals();
		return triangles;
	}

	/*	Prints the vertices array
	*/
	void printVertices() {
		for (int i = 0; i < vertices.size(); i++) {
			cout << vertices[i] << endl;
		}
	}

	/*	Prints the faces array
	*/
	void printFaces() {
		for (int i = 0; i < faces.size(); i++) {
			cout << faces[i] << endl;
		}	
	}

	/*	Prints the normals array
	*/
	void printNormals() {
		for (int i = 0; i < normals.size(); i++) {
			cout << normals[i] << endl;
		}	
	}

	/* Gets the size of vertices array
	*/
	int getVerticesSize() {
		return vertices.size();
	}

	/*	Gets the size of the faces arra
	*/
	int getFacesSize() {
		return faces.size();	
	}

	vector<vec3> normals;
	vector<vec3> vertices;
	private:
		vector<vec3> faces;	// length = # of triangles
		int numVertices;
		int numFaces;
		vec3 kd;
		vec3 ks;
		char* fileName; 
};

#endif
