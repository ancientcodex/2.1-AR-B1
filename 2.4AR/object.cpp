#include "3D.h"
#include "FpsCam.h"
#include "time.h"
#include "ObjModel.h"
#include <array>
#include <iostream>
#include "textOutput.h"
#include "Player.h"
#include <fstream>
#include <iostream> 

int size = 2;
int cubeXPositions[2];
int cubeYPositions[2];

//for cleanup
//ObjModel modelT;
std::shared_ptr<DataManager> dataManager;

GLFWwindow* window;
ObjModel* objmodelr;
ObjModel* objmodell;

std::list<std::string> players;
bool gameOnPause;
bool gameIsFinished;
textOutput mainText;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 lefthand = glm::mat4(1.0f);
glm::mat4 righthand = glm::mat4(1.0f);


void startup(std::shared_ptr<DataManager> dManager)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();
	init();
	dataManager = dManager;

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

FpsCam* camera;
//INIT METHOD RUN AT START
void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);

			if (key == GLFW_KEY_P)
			{
				//TODO: game pause method
				gameOnPause = true;

			}

			if (key == GLFW_KEY_S)
			{
				//TODO: game start method
				gameOnPause = false;
			}
		});
	camera = new FpsCam(window);
	objmodell = new ObjModel("data/leftHand.obj");
	objmodelr = new ObjModel("data/rightHand.obj");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	ranPos();
	//modelT = new ObjModel("models/car/honda_jazz.obj");

	std::ifstream input("gamesplayer.txt");
	if (input.fail())
	{
		std::cout << "File could not be opened" << std::endl;
		return;
	}
	std::string info;
	while (std::getline(input, info))
	{
		players.push_front(info);
	}

	//set status boolean
	gameOnPause = false;
	gameIsFinished = false;

	//Init to draw texts
	mainText.init();

	//TODO: Diffrent place will help openGL to run better
	if (gameIsFinished)
	{
		//get name
		std::string name;
		std::cout << "fill in name: (max 8 characters)" << std::endl;
		std::cin >> name;
		int sizeName = name.size();
		if (sizeName > 8)
		{
			std::cout << "fill in name: (max 8 characters)" << std::endl;
			std::cin >> name;
			int sizeName = name.size();
		}
		else
		{
			//fill in right value of points for player
			Player player(name, 1);
			std::string t = player.toString();
			players.push_front(t);

			//safe player to txt
			std::ofstream output("gamesplayer.txt", std::ios_base::app);
			output << t << std::endl;
			std::cout << "play saved" << std::endl;
			output.close();

			gameIsFinished = false;
		}
	}
}

float angle = 0.0f;
float speed = 0.0f;
float red = 0.0f;
float blue = 0.0f;
float green = 0.0f;
float pos = 0.0f;



void update()
{
	camera->update(window);

	if (pos >= 15.0f)
	{
		pos = 0.0f;
		ranPos();
	}
	angle += 0.01f;
	speed += 0.02f;
	pos += 0.01f;

}

void draw()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), width / (float)height, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());

	glEnable(GL_DEPTH_TEST);

	std::tuple<std::string, cv::Point> temp;

	temp = dataManager->getPoint();
	createLeftHand(temp);
	createRightHand(temp);
	temp = dataManager->getPoint();
	createLeftHand(temp);
	createRightHand(temp);


	for (int i = 0; i < size; i++)
	{
		cubeCreate(cubeXPositions[i], cubeYPositions[i]);
	}

	for (int i = 0; i < size; i++)
	{
		cubeCreate(cubeXPositions[i], cubeYPositions[i]);
	}

	writeTextAction();
	writePlayerScoreList();
}

void createBackground()
{
	glm::mat4 background = glm::mat4(1.0f);
	background = glm::translate(background, glm::vec3(0, 0, -50));



	tigl::shader->setModelMatrix(background);
	tigl::shader->enableColor(false);
	tigl::shader->enableTexture(true);

	tigl::begin(GL_QUADS);

	tigl::addVertex(Vertex::PC(glm::vec3(-100, 100, 0), glm::vec4(red, blue, blue, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(100, 100, 0), glm::vec4(blue, green, red, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(100, -100, 0), glm::vec4(red, green, blue, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-100, -100, 0), glm::vec4(green, green, blue, 1)));

	tigl::end();

}
cv::Point lastTargetR;
glm::vec3 handPosR = glm::vec3(0.0f, 0.0f, -3.0f);
void createRightHand(std::tuple<std::string, cv::Point> t)
{
	cv::Point target;
	float handspeed = 0.05f;
	if (std::get<0>(t) == "handR") {
		//targeting
		target = std::get<1>(t);
		lastTargetR = target;
	}
	target = lastTargetR;
	handPosR.x += -0.5f + (float)(((target.x / 10) - handPosR.x) * handspeed);
	handPosR.y += -0.5f + (float)(((target.y / 10) - handPosR.y) * handspeed);

	glm::mat4 righthand(1.0f);
	//righthand = glm::rotate(righthand, 0.5f, glm::vec3(0, 1, 0));
	righthand = glm::translate(righthand, handPosR);

	tigl::shader->setModelMatrix(righthand);
	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(false);

	objmodelr->draw();
}

cv::Point lastTargetL;
glm::vec3 handPosL = glm::vec3(0.0f,0.0f,-3.0f);
void createLeftHand(std::tuple<std::string, cv::Point> t)
{
	cv::Point target;
	float handspeed = 0.05f;
	if (std::get<0>(t) == "handL") {
		//targeting
		target = std::get<1>(t);
		lastTargetL = target;
	}
	target = lastTargetL;
	handPosL.x += -0.5f + (float)(((target.x / 10) - handPosL.x ) * handspeed);
	handPosL.y += -0.5f + (float)(((target.y / 10) - handPosL.y ) * handspeed);

	glm::mat4 lefthand(1.0f);
	//lefthand = glm::rotate(lefthand, 0.5f, glm::vec3(0, 0, 1));
	lefthand = glm::translate(lefthand, handPosL);

	tigl::shader->setModelMatrix(lefthand);
	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(false);

	//std::cout << " x: " << handPosL.x << " y: " << handPosL.y << std::endl;

	objmodell->draw();
}


void cubeCreate(int x, int y)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, -40));

	//(x-as, y-as, z-as) (left/right, up/down, front/back)
	model = glm::translate(model, glm::vec3(0, 0, pos));
	model = glm::rotate(model, angle, glm::vec3(1, 1, 0));

	tigl::shader->setModelMatrix(model);
	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(false);

	tigl::begin(GL_QUADS);

	//achterkant
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(red, green, 0, 1)));

	//voorkant
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(red, green, 0, 1)));

	//onderkant
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(red, green, 0, 1)));

	//bovenkant
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, green, 0, 1)));

	//rechterkant
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(red, green, 0, 1)));
	//linkerkant
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(red, green, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(red, green, 0, 1)));

	tigl::end();
}

void ranPos()
{
	for (int i = 0; i < size; i++)

	{
		int clr = (rand() % 2);
		red = 255;
		green = 255;
		if (clr == 1)
		{
			red = 255;
			green = 0;
		}
		else if (clr == 2)
		{
			red = 0;
			green = 255;
		}
		cubeXPositions[i] = (rand() % 50) - 24;
		cubeYPositions[i] = (rand() % 30) - 14;
		std::cout << "X: " << cubeXPositions[i] << ". Y: " << cubeYPositions[i] << ". ";
	}
}

void writeTextAction()
{
	//Get fitting text for status of the game

	if (gameOnPause)
	{
		mainText.draw("Press 'S' to start", 0, 32);
	}
	else
	{
		mainText.draw("Press 'P' to pause", 0, 32);
	}

}

void writePlayerScoreList()
{
	std::list<std::string>::iterator it;
	int  i = 32;
	for (it = players.begin(); it != players.end(); ++it)
	{
		mainText.draw(*it, 1100, i);
		i += 32;
	}
}