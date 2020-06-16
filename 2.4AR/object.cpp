#include "3D.h"
#include "FpsCam.h"
#include "time.h"
#include "ObjModel.h"
#include <array>
#include <iostream>
#include "textOutput.h"

GLFWwindow* window;
ObjModel* modelT;
textOutput mainText;
int size = 2;
int cubeXPositions[2];
int cubeYPositions[2];

void ranPos();
void cubeCreate(int x, int y);
glm::mat4 model = glm::mat4(1.0f);

void startup() 
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

void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });
    camera = new FpsCam(window);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_DEPTH_TEST);
	srand(time(NULL));
	ranPos();
	modelT = new ObjModel("models/car/honda_jazz.obj");
	
	//Init to draw texts
	mainText.init();
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

    if (red >= 1.0f) 
    {
        red = 0.01f;
    }
    if (blue >= 1.0f)
    {
        blue = 0.01f;
    }
    if (green >= 1.0f)
    {
        green = 0.01f;
    }
	if (pos >= 15.0f)
	{
		pos = 0.0f;
		ranPos();
	}
    angle += 0.01f;
    speed += 0.02f;
    pos += 0.01f;
    
    red += 0.00011f;
    blue += 0.00023f;
    green += 0.00037f;
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

	//tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::shader->enableColor(true);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < size; i++)
	{
		cubeCreate(cubeXPositions[i], cubeYPositions[i]);
	}
	//Draw text
	mainText.draw("Dit is een andere test", 0, 32);
	mainText.draw("Dit is een test", 0, 32);
}


	void cubeCreate(int x, int y)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y, -10));

		//(x-as, y-as, z-as) (left/right, up/down, front/back)
		model = glm::translate(model, glm::vec3(0, 0, pos));

		model = glm::rotate(model, angle, glm::vec3(1, 1, 0));

		tigl::shader->setModelMatrix(model);
		tigl::begin(GL_QUADS);

		//achterkant
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(red, blue, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(blue, green, red, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(red, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(green, green, blue, 1)));

		//voorkant
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(blue, blue, red, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(green, red, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(red, green, blue, 1)));

		//onderkant
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(red, blue, green, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(green, red, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(red, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(green, green, red, 1)));

		//bovenkant
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(green, red, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(red, blue, green, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(blue, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, blue, green, 1)));

		//rechterkant
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -1), glm::vec4(blue, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, 1, 1), glm::vec4(red, green, green, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, 1), glm::vec4(green, red, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -1), glm::vec4(red, green, red, 1)));

		//linkerkant
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -1), glm::vec4(red, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, 1), glm::vec4(blue, blue, red, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, 1), glm::vec4(red, green, blue, 1)));
		tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -1), glm::vec4(green, red, blue, 1)));

		tigl::end();
	}

	void ranPos()
	{
		for (int i = 0; i < size; i++)
		{
			cubeXPositions[i] = (rand() % 50) -24;
			cubeYPositions[i] = (rand() % 30) - 14;
			std::cout << "X: " << cubeXPositions[i] << ". Y: " << cubeYPositions[i] << ". ";
		}
	}

