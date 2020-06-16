#define _CRT_SECURE_NO_WARNINGS
#include "textOutput.h"

textOutput::textOutput()
{
}

void textOutput::init()
{
	//TODO: streams
	//buffer voor bestand data
	unsigned char* ttf_buffer = new unsigned char[1 << 20];
	//texture data
	unsigned char* temp_bitmap = new unsigned char[512 * 512];
	//leest 2^20 data van bestand
	fread(ttf_buffer, 1, 1 << 20, fopen("c:/windows/fonts/times.ttf", "rb"));
	//texture data genereren
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits! //ctlr/shift/spatie
	//texture aanmaken
	glGenTextures(1, &texId);
	//texture binden
	glBindTexture(GL_TEXTURE_2D, texId);
	//texture data naar openGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	//texture instellen
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//opruimen buffers
	delete[] ttf_buffer;
	delete[] temp_bitmap;
}

void textOutput::draw(const std::string& text, float x, float y)
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	tigl::shader->setProjectionMatrix(glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, -100.0f, 100.0f));
	tigl::shader->setViewMatrix(glm::mat4(1.0f));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(false);
	tigl::shader->enableLighting(false);
	tigl::shader->enableTexture(true);
	tigl::shader->enableColorMult(false);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texId);

	stbtt_aligned_quad q;
	tigl::begin(GL_QUADS);
	for (int i = 0; i < text.size(); i++) {
		if (text[i] >= 32 && text[i] < 128) {
			stbtt_GetBakedQuad(cdata, 512, 512, text[i] - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
			tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y0, 0), glm::vec2(q.s0, q.t0)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y0, 0), glm::vec2(q.s1, q.t0)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y1, 0), glm::vec2(q.s1, q.t1)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y1, 0), glm::vec2(q.s0, q.t1)));
		}
	}
	tigl::end();
}

void textOutput::update(GLFWwindow* window)
{
}
