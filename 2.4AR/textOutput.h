#pragma once
#include <glm/glm.hpp>
#include "tigl.h"
using tigl::Vertex;
#include "stb_truetype.h"
#include <string>
#include <list>
struct GLFWwindow;
#include <glm/gtc/matrix_transform.hpp>

class textOutput
{
public:
	stbtt_bakedchar cdata[96];
	GLuint texId;

	textOutput();
	virtual void init();
	virtual void draw(const std::string& text, float x, float y);
	virtual void update(GLFWwindow* window);
};

