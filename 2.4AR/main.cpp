#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "3D.h"
#include "VisionManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//thread t1(startup);
	thread t2(&VisionManager::updater,VisionManager());
	//t1.join();
	t2.join();
	return 0;
}
