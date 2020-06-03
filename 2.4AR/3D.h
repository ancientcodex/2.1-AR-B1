#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "DataManager.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

void startup(std::shared_ptr<DataManager> dManager);
void init();
void update();
void draw();
void ranPos();
void createBackground();
void cubeCreate(int x, int y);