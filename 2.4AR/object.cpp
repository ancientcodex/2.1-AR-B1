#include "3D.h"

int size = 2; // amount of cubes at the time.
int roundcount = 0;
int cubeXPositions[2];
int cubeYPositions[2];
cv::Point redCube;
cv::Point greenCube;


/*
  TODO: make all of the different methods into small classes
  for cleanup of the deamon child!
*/
std::shared_ptr<DataManager> dataManager;
GLFWwindow* window;
ObjModel* objmodelr;
ObjModel* objmodell;
std::list<std::string> players;
bool gameOnPause = true;
bool gameIsFinished = false;
textOutput mainText;
glm::mat4 lefthand = glm::mat4(1.0f);
glm::mat4 righthand = glm::mat4(1.0f);
FpsCam* camera;
float angle = 0.0f;
float speed = 0.0f;
float pos = 0.0f;
int score = 0;
//for hand this must go in a class at a later iteration
cv::Point lastTargetR;
glm::vec3 handPosR = glm::vec3(0.0f, 0.0f, 3.0f);
cv::Point lastTargetL;
glm::vec3 handPosL = glm::vec3(0.0f, 0.0f, 3.0f);


void startup(std::shared_ptr<DataManager> dManager)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Game", NULL, NULL);
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
		//while (!gameOnPause)
		//{
		update();
		draw();
		//}
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
}

//INIT METHOD RUN AT START
void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_P:
				gameOnPause = true;
				if(roundcount > 20){
					roundcount = 0;
					score = 0;
				}
				break;
			case GLFW_KEY_S:
				gameOnPause = false;
				if(roundcount > 20){
					roundcount = 0;
					score = 0;
				}
				if (dataManager != NULL) dataManager->clearBuffer();
				break;
			}
		});
	camera = new FpsCam(window);
	objmodell = new ObjModel("data/leftHand.obj");
	objmodelr = new ObjModel("data/rightHand.obj");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	ranPos();

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

	//Init to draw texts
	mainText.init();

}

void update()
{
	if (roundcount >= 20) {
		gameIsFinished = true;
	}
	camera->update(window);
	if (!gameOnPause ) {
		if (pos >= 18.0f)
		{
			pos = 0.0f;
			ranPos();
			roundcount++;
		}
		angle += 0.04f;
		pos += 0.02f;


	}
	checkEndGame();
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
	// eye is camera position, center is where you look at and up is which direction is up.
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(view);

	glEnable(GL_DEPTH_TEST);
	if (!gameOnPause) {
		cv::Point left, right;
		std::tuple<std::string, cv::Point> temp;
		temp = dataManager->getPoint();
		createLeftHand(temp);
		createRightHand(temp);
		left = std::get<1>(temp);
		temp = dataManager->getPoint();
		createLeftHand(temp);
		createRightHand(temp);
		right = std::get<1>(temp);
		collisionDetection();
		
	}
	writeTextAction();
	writePlayerScoreList();
}
//colision detection
void collisionDetection() {
	bool color = false;
	bool leftColor = false;
	bool rightColor = false;
	float lClosest = 0, rClosest = 0;

	//distance
	float dRedL = calculateDistance(handPosL.x, handPosL.y, redCube.x, redCube.y);
	float dGreenL = calculateDistance(handPosL.x, handPosL.y, greenCube.x, greenCube.y);

	float dRedR = calculateDistance(handPosR.x, handPosR.y, redCube.x, redCube.y);
	float dGreenR = calculateDistance(handPosR.x, handPosR.y, greenCube.x, greenCube.y);

	for (int i = 0; i < size; i++)
	{
		bool collision = false;
		float margin = 6.5f;
		if (pos > 5 && (cubeXPositions[i] >= (handPosL.x - margin) && cubeXPositions[i] <= (handPosL.x + margin)) && (cubeYPositions[i] >= (handPosL.y - margin) && cubeYPositions[i] <= (handPosL.y + margin)))
		{
			if (dRedL > dGreenL) {
				lClosest = dGreenL;
				leftColor = true;
			}
			else
			{
				lClosest = dRedL;
				leftColor = false;
			}

			pos = 0.0f;
			collision = true;
		}
		if (pos > 5 && (cubeXPositions[i] >= (handPosR.x - margin) && cubeXPositions[i] <= (handPosR.x + margin)) && (cubeYPositions[i] >= (handPosR.y - margin) && cubeYPositions[i] <= (handPosR.y + margin)))
		{

			if (dRedR > dGreenR) {
				rClosest = dGreenR;
				rightColor = true;
			}
			else {
				rClosest = dRedR;
				rightColor = false;
			}

			pos = 0.0f;
			collision = true;
		}
		if (collision) {
			if (lClosest < rClosest) {
				if (rightColor) {
					score++;
					std::cout << "right hand kills green cube" << std::endl;
				}
				if (!rightColor) {
					score--;
					std::cout << "right hand kills red cube" << std::endl;
				}
				std::cout << "right hand kills cube" << std::endl;
				ranPos();
				roundcount++;
			}
			else {
				if (leftColor) {
					score++;
					std::cout << "left hand kills green cube" << std::endl;
				}
				if (!leftColor) {
					score--;
					std::cout << "left hand kills red cube" << std::endl;
				}
				ranPos();
				roundcount++;
			}
		}
		else
		{
			if (!color)
				cubeCreate(cubeXPositions[i], cubeYPositions[i], 0);
			else
				cubeCreate(cubeXPositions[i], cubeYPositions[i], 1);
			color = !color;
		}
	}
}

float calculateDistance(float x1, float y1, float x2, float y2) {
	return sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void createBackground()
{
	glm::mat4 background = glm::mat4(1.0f);
	background = glm::translate(background, glm::vec3(0, 0, -50));

	int red = 0;
	int blue = 0;
	int green = 0;

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

void createRightHand(std::tuple<std::string, cv::Point> t)
{
	float offsetX = -0.0f;
	float offsetY = -0.0f;
	cv::Point target;
	float handspeed = 0.05f;
	if (std::get<0>(t) == "handR") {
		//targeting
		target = std::get<1>(t);
		lastTargetR = target;
	}
	target = lastTargetR;
	handPosR.x += (float)((((target.x * 0.021875f) - handPosR.x) + offsetX) * handspeed);
	handPosR.y += (float)((((target.y * 0.017f) - handPosR.y) + offsetY) * handspeed);

	glm::mat4 righthand(1.0f);
	//righthand = glm::rotate(righthand, 0.5f, glm::vec3(0, 1, 0));
	righthand = glm::translate(righthand, -handPosR);
	//righthand = glm::translate(righthand, glm::vec3(0, -3, 0));

	tigl::shader->setModelMatrix(righthand);
	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(false);

	objmodelr->draw();
}

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

	handPosL.x += (float)(((target.x * 0.021875f) - handPosL.x) + 0) * handspeed;
	handPosL.y += (float)(((target.y * 0.017f) - handPosL.y)) * handspeed;


	glm::mat4 lefthand(1.0f);
	//lefthand = glm::rotate(lefthand, 0.5f, glm::vec3(0, 0, 1));
	lefthand = glm::translate(lefthand, -handPosL);
	//lefthand = glm::translate(lefthand, glm::vec3(0, -3, 0));


	tigl::shader->setModelMatrix(lefthand);
	tigl::shader->enableColor(true);
	tigl::shader->enableTexture(false);

	//std::cout << " x: " << handPosL.x << " y: " << handPosL.y << std::endl;

	objmodell->draw();
}


void cubeCreate(int x, int y, int color)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, -40));

	int red = 0;
	int green = 0;
	if (color == 0)
	{
		red = 255;
		redCube = cv::Point(x, y);
	}
	else if (color == 1)
	{
		green = 255;
		greenCube = cv::Point(x, y);
	}

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
		cubeXPositions[i] = (rand() % 30) - 15;
		cubeYPositions[i] = (rand() % 20) - 10;
		std::cout << "X: " << cubeXPositions[i] << ". Y: " << cubeYPositions[i] << ". ";
	}
}

void writeTextAction()
{
	//Get fitting text for status of the game
	std::string scoreText = "score: " + std::to_string(score);
	std::string roundText = "round: " + std::to_string(roundcount) + " / 20";
	if (gameOnPause)
	{
		mainText.draw("Press 'S' to start", 0, 32);
	}
	else
	{
		mainText.draw("Press 'P' to pause", 0, 32);
	}
	mainText.draw(scoreText, 0, 64);
	mainText.draw(roundText, 0, 96);

}

void checkEndGame(){
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
			Player player(name, score);
			std::string t = player.toString();
			players.push_front(t);

			//safe player to txt
			std::ofstream output("gamesplayer.txt", std::ios_base::app);
			output << t << std::endl;
			std::cout << "play saved" << std::endl;
			output.close();

			gameIsFinished = false;
			roundcount = 0;
			score = 0;
			gameOnPause = true;
		}
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