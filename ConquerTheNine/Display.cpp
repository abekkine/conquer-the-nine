#include "Display.h"

#include <iostream>

#include <math.h>

#include "Exception.h"
#include "TextManager.h"

Display* Display::instance_ = 0;

Display::Display()
{
	std::cout << "Display::Display()" << std::endl;
}

Display* Display::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new Display();
	}

	return instance_;
}

Display::~Display()
{
	std::cout << "Display::~Display()" << std::endl;
}

// BEGIN static callbacks
void Display::errorCallback(int error, const char* description)
{
	Display::Instance()->ErrorHandler(error, std::string(description));
}

void Display::keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	Display::Instance()->KeyHandler(w, key, scancode, action, mods);
}

void Display::mouseButtonCallback(GLFWwindow* w, int button, int action, int mods)
{
	Display::Instance()->MouseButtonHandler(w, button, action, mods);
}

void Display::cursorPositionCallback(GLFWwindow* w, double x, double y)
{
	Display::Instance()->CursorPositionHandler(w, x, y);
}

void Display::scrollCallback(GLFWwindow* w, double x, double y)
{
	Display::Instance()->MouseScrollHandler(w, x, y);
}

void Display::resizeCallback(GLFWwindow* w, int width, int height)
{
	Display::Instance()->ResizeHandler(w, width, height);
}
// END static callbacks

// BEGIN handlers
void Display::ErrorHandler(int error, std::string description)
{
	std::cout << "GLFX ERROR: " << description << std::endl;
}

void Display::ResizeHandler(GLFWwindow* w, int width, int height)
{
	std::cout << "Display::ResizeHandler()" << std::endl;
	glViewport(0, 0, width, height);
}

void Display::KeyHandler(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	std::cout << "Display::KeyHandler()" << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, GLFW_TRUE);
	}
	else {
		switch (key)
		{
		default:
			std::cout << "    ";
			std::cout << "key(" << key << "), ";
			std::cout << "scancode(" << scancode << "), ";
			std::cout << "action(" << action << "), ";
			std::cout << "mods(" << mods << ")" << std::endl;
		}
	}
}

void Display::CursorPositionHandler(GLFWwindow* w, double x, double y)
{
	std::cout << "Display::CursorPositionHandler()" << std::endl;
	std::cout << "    cursor @ (" << x << ", " << y << ")" << std::endl;
}

void Display::MouseButtonHandler(GLFWwindow* w, int button, int action, int mods)
{
	std::cout << "Display::MouseButtonHandler()" << std::endl;
	std::cout << "    ";
	std::cout << "button(" << button << "), ";
	std::cout << "action(" << action << "), ";
	std::cout << "mods(" << mods << ")" << std::endl;
}

void Display::MouseScrollHandler(GLFWwindow* w, double x, double y)
{
	std::cout << "Display::MouseScrollHandler()" << std::endl;
	std::cout << "    ";
	std::cout << "scroll @ (" << x << ", " << y << ")" << std::endl;
}
// END handlers

void Display::InitDisplay()
{
	std::cout << "Display::InitDisplay()" << std::endl;
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		throw Exception("GLFW init failed!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// TODO : Window properties should be given by derived game class.
	window_ = glfwCreateWindow(800, 800, "Ct9", NULL, NULL);
	if (!window_)
	{
		glfwTerminate();
		throw Exception("GLFW window creation failed!");
	}

	glfwSetKeyCallback(window_, keyCallback);
	glfwSetFramebufferSizeCallback(window_, resizeCallback);
	glfwSetCursorPosCallback(window_, cursorPositionCallback);
	glfwSetMouseButtonCallback(window_, mouseButtonCallback);
	glfwSetScrollCallback(window_, scrollCallback);

	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1);

	try {
		TextManager::Instance()->AddFont("ubuntu", "c:/source/fonts/ubuntumono/ubuntu44mono-r.ttf");
		TextManager::Instance()->AddFont("droid", "c:/source/fonts/droidsansmono/droids44ansmono.ttf");
		TextManager::Instance()->AddFont("anonym", "c:/source/fonts/anonymouspro/anony44mous_pro.ttf");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	TextManager::Instance()->Init();
}

void Display::RenderWorldContents()
{
	static double a = 0.0;
	double s;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(a, 0.0f, 0.0f, 1.0f);
	a += 1.0;
	s = 0.46 + 0.04*sin(12.0* a * 3.14159 / 180.0);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2d(-s, -s);
	glVertex2d(s, -s);
	glVertex2d(s, s);
	glVertex2d(-s, s);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2d(-0.5, -0.5);
	glVertex2d(0.5, -0.5);
	glVertex2d(0.5, 0.5);
	glVertex2d(-0.5, 0.5);
	glEnd();

	glPopMatrix();
}

void Display::RenderScreenContents()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 800, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(300, 50);
	TextManager::Instance()->UseFont("anonym", 40);
	TextManager::Instance()->Render("Anonymous Pro, 40");

	glRasterPos2i(300, 100);
	TextManager::Instance()->UseFont("droid", 40);
	TextManager::Instance()->Render("Droid Sans Mono, 40");

	glRasterPos2i(300, 150);
	TextManager::Instance()->UseFont("ubuntu", 40);
	TextManager::Instance()->Render("Ubuntu Mono, 40");
}

void Display::Run()
{
	std::cout << "Display::Run()" << std::endl;
	while (!glfwWindowShouldClose(window_))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		RenderWorldContents();

		RenderScreenContents();

		glfwSwapBuffers(window_);

		glfwPollEvents();
	}

	glfwTerminate();
}
