#include "3D.h"
#include "FpsCam.h"
#include "time.h"
#include "ObjModel.h"
#include <array>
#include <iostream>

GLFWwindow* window;
ObjModel* objmodel;
GLuint textureId = -1;

int size = 2;
int cubeXPositions[2];
int cubeYPositions[2];

void startup(std::shared_ptr<DataManager> dManager)
{
void ranPos();
void cubeCreate(int x, int y);
void createBackground();

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 background = glm::mat4(1.0f);
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

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();

        std::tuple<std::string, cv::Point> t = dManager->getPoint();
        std::string s = std::get<0>(t);
        cv::Point p = std::get<1>(t);
        std::cout << s << " center: x: " << p.x << " y: " << p.y << std::endl;

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
    });
    camera = new FpsCam(window);
    objmodel = new ObjModel("data/RiggedHand.obj");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	ranPos();
	objmodel = new ObjModel("models/car/honda_jazz.obj");

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	char data[32 * 32 * 4];
	for (int i = 0; i < 32 * 32 * 4; i++)
		data[i] = rand() % 255;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());

	glEnable(GL_DEPTH_TEST);

	createBackground();

	for (int i = 0; i < size; i++)
	{
		cubeCreate(cubeXPositions[i], cubeYPositions[i]);
	}
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
		cubeXPositions[i] = (rand() % 50) -24;
		cubeYPositions[i] = (rand() % 30) - 14;
		std::cout << "X: " << cubeXPositions[i] << ". Y: " << cubeYPositions[i] << ". ";
		}
	}