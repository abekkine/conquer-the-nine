#include "Display.h"

#include <iostream>

#include "Exception.h"
#include "TextManager.h"
#include "GameState.h"

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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		GameState::Instance()->State(GameState::gsMENU);
	}
	else {
		ObjContainerType::const_iterator it;
		for (it = objects_.begin(); it != objects_.end(); ++it)
		{
			(*it)->KeyEvent(key, scancode, action, mods);
		}
	}
}

void Display::CursorPositionHandler(GLFWwindow* w, double x, double y)
{
	ObjContainerType::const_iterator it;
	for (it = objects_.begin(); it != objects_.end(); ++it)
	{
		(*it)->CursorPositionEvent(x, y);
	}
}

void Display::MouseButtonHandler(GLFWwindow* w, int button, int action, int mods)
{
	ObjContainerType::const_iterator it;
	for (it = objects_.begin(); it != objects_.end(); ++it)
	{
		(*it)->MouseButtonEvent(button, action, mods);
	}
}

void Display::MouseScrollHandler(GLFWwindow* w, double x, double y)
{
	std::cout << "Display::MouseScrollHandler()" << std::endl;
	std::cout << "    ";
	std::cout << "scroll @ (" << x << ", " << y << ")" << std::endl;
}
// END handlers

void Display::AddDisplayObject(DisplayObjectInterface* obj)
{
	std::cout << "Display::AddDisplayObject()" << std::endl;
	objects_.push_back(obj);
}

void Display::InitObjects()
{
	ObjContainerType::const_iterator it;
	DisplayObjectInterface* iObject;

	for (it = objects_.begin(); it != objects_.end(); ++it)
	{
		iObject = *it;
		iObject->Init();
	}
}

void Display::Init()
{
	InitDisplay();
	InitObjects();
}

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
}

void Display::UpdateViewport(DisplayObjectInterface::Viewport& vp)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(vp.left, vp.right, vp.bottom, vp.top, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void Display::RenderContents()
{
	RenderObjects();
	RenderState();
}

void Display::RenderObjects()
{
	ObjContainerType::const_iterator it;
	DisplayObjectInterface* iObject;
	for (it = objects_.begin(); it != objects_.end(); ++it)
	{
		iObject = *it;
		UpdateViewport(iObject->GetViewport());
		iObject->Render();
	}
}

void Display::RenderState()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 800, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	TextManager::Instance()->UseFont("", 20);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(20, 20);
	TextManager::Instance()->Render(GameState::Instance()->StateName());
}

void Display::Run()
{
	std::cout << "Display::Run()" << std::endl;
	while (!glfwWindowShouldClose(window_))
	{
		if (GameState::Instance()->State() == GameState::gsQUIT)
		{
			glfwSetWindowShouldClose(window_, GLFW_TRUE);
		}

		glClear(GL_COLOR_BUFFER_BIT);

		RenderContents();

		glfwSwapBuffers(window_);

		glfwPollEvents();
	}

	glfwTerminate();
}
