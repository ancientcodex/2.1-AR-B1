#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "3D.h"
#include "VisionManager.h"
#include <thread>
#include "main.h"
#include "DataManager.h"

int main(int argc, char* argv[])
{
	DataManager dataManager;
	VisionManager v(&dataManager);
	
	startup();
	std::thread t2(&VisionManager::updater,v);
	t2.join();
	return 0;
}