#pragma once

#include "GL.h"

#include <vector>

namespace gdp
{
	class Model {
	public:
		Model(const char* filepath);
		~Model();

		GLuint Vbo;
		GLuint VertexBufferId;
		GLuint IndexBufferId;

		std::vector<glm::vec3> vertices;

		unsigned int NumTriangles;
	};
}