#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "DataManager.h"
#include "FpsCam.h"
#include "time.h"
#include "ObjModel.h"
#include <array>
#include <iostream>
#include "textOutput.h"
#include "Player.h"
#include <fstream>
#include <iostream> 
#include <math.h> 
#include "Texture.h"

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
void cubeCreate(int x, int y, int color);
void checkEndGame();
void createLeftHand(std::tuple<std::string, cv::Point> t);
void createRightHand(std::tuple<std::string, cv::Point> t);
void writeTextAction();
void writePlayerScoreList();
float calculateDistance(float x1, float y1, float x2, float y2);
void collisionDetection();
