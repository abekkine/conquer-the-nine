#include "Display.h"

#include <iostream>

#include "Exception.h"
#include "TextManager.h"
#include "GameState.h"

#include "version.h"

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
	scrWidth_ = width;
	scrHeight_ = height;
	glViewport(0, 0, scrWidth_, scrHeight_);
}

void Display::KeyHandler(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	bool dispatch = false;
	LayerContainerType::const_iterator i;
	ObjContainerType::const_iterator j;
	for (i = layers_.begin(); i != layers_.end(); ++i)
	{
		for (j = (i->second).objects.begin(); j != (i->second).objects.end(); ++j)
		{
			dispatch = (*j)->KeyEvent(key, scancode, action, mods);
			if (dispatch) break;
		}
		if (dispatch) break;
	}
}

void Display::CursorPositionHandler(GLFWwindow* w, double x, double y)
{
	LayerContainerType::const_iterator i;
	ObjContainerType::const_iterator j;
	for (i = layers_.begin(); i != layers_.end(); ++i)
	{
		for (j = (i->second).objects.begin(); j != (i->second).objects.end(); ++j)
		{
			(*j)->CursorPositionEvent(x, y);
		}
	}
}

void Display::MouseButtonHandler(GLFWwindow* w, int button, int action, int mods)
{
	LayerContainerType::const_iterator i;
	ObjContainerType::const_iterator j;
	for (i = layers_.begin(); i != layers_.end(); ++i)
	{
		for (j = (i->second).objects.begin(); j != (i->second).objects.end(); ++j)
		{
			(*j)->MouseButtonEvent(button, action, mods);
		}
	}
}

void Display::MouseScrollHandler(GLFWwindow* w, double x, double y)
{
	std::cout << "Display::MouseScrollHandler()" << std::endl;
	std::cout << "    ";
	std::cout << "scroll @ (" << x << ", " << y << ")" << std::endl;
}
// END handlers

void Display::AddDisplayObject(std::string layer, DisplayObjectInterface* obj)
{
	std::cout << "Display::AddDisplayObject()" << std::endl;
	LayerContainerType::iterator f = layers_.find(layer);
	if (f != layers_.end())
	{
		// Add to existing layer.
		(f->second).objects.push_back(obj);
	}
	else
	{
		// New layer.
		LayerObject L;
		L.objects.push_back(obj);
		layers_[layer] = L;
	}
}

Display::Viewport* Display::AddLayerViewport(std::string layer, Viewport viewport)
{
	std::cout << "Display::AddLayerViewport()" << std::endl;
	LayerContainerType::iterator f = layers_.find(layer);
	if (f != layers_.end())
	{
		// Set viewport of existing layer.
		(f->second).viewport = viewport;
		return &((f->second).viewport);
	}
	else
	{
		// New layer
		LayerObject L;
		L.viewport = viewport;
		layers_[layer] = L;

		return &(layers_[layer].viewport);
	}
}

void Display::InitObjects()
{
	LayerContainerType::const_iterator i;
	ObjContainerType::const_iterator j;

	for (i = layers_.begin(); i != layers_.end(); ++i)
	{
		for (j = (i->second).objects.begin(); j != (i->second).objects.end(); ++j)
		{
			(*j)->Init();
		}
	}
}

void Display::Init()
{
	InitDisplay();
	InitObjects();
}

void Display::FullScreen(bool value)
{
	fullScreen_ = value;
}

void Display::WindowSize(int w, int h)
{
	reqWidth_ = w;
	reqHeight_ = h;
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// DEBUG : Windowed
	scrWidth_ = reqWidth_;
	scrHeight_ = reqHeight_;
	if (fullScreen_)
	{
		// True full screen
		window_ = glfwCreateWindow(scrWidth_, scrHeight_, "Ct9", glfwGetPrimaryMonitor(), NULL);
		// NOTE : Windowed full screen; which is faster, but based on desktop resolution.
		//{
		//	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		//	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		//	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		//	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		//	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		//	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		//  scrWidth_ = mode->width;
		//  scrHeight_ = mode->height;
		//	window_ = glfwCreateWindow(scrWidth_, scrHeight_, "Ct9", monitor, NULL);
		//}
	}
	else
	{
		window_ = glfwCreateWindow(scrWidth_, scrHeight_, "Ct9", NULL, NULL);
	}

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::UpdateViewport(Viewport& vp)
{
	// Calculate viewport
	double realWidth = scrWidth_ * vp.unitsPerPixel;
	double realHeight = scrHeight_ * vp.unitsPerPixel;
	double vpLeft, vpRight, vpTop, vpBottom;

	if (vp.type == vtCenterOrigin)
	{
		vpLeft = vp.cx - 0.5 * realWidth;
		vpRight = vp.cx + 0.5 * realWidth;
		vpTop = vp.cy + 0.5 * realHeight;
		vpBottom = vp.cy - 0.5 * realHeight;
	}
	else if (vp.type == vtBottomLeftOrigin)
	{
		vpLeft = vp.cx;
		vpBottom = vp.cy;
		vpRight = vp.cx + realWidth;
		vpTop = vp.cy + realHeight;
	}
	else // if (vp.type == vtTopLeftOrigin)
	{
		vpLeft = vp.cx;
		vpTop = vp.cy;
		vpRight = vp.cx + realWidth;
		vpBottom = vp.cy + realHeight;
	}
	// End
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(vpLeft, vpRight, vpBottom, vpTop, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void Display::RenderContents()
{
	RenderObjects();
	RenderState();
}

void Display::RenderObjects()
{
	LayerContainerType::const_iterator i;
	ObjContainerType::const_iterator j;

	for (i = layers_.begin(); i != layers_.end(); ++i)
	{
		UpdateViewport((Viewport&)(i->second).viewport);
		for (j = (i->second).objects.begin(); j != (i->second).objects.end(); ++j)
		{
			(*j)->Render();
		}
	}
}

void Display::RenderState()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, scrWidth_, 0, scrHeight_, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	TextManager::Instance()->UseFont("ubuntu", 20);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(10, 30);
	TextManager::Instance()->Render(GameState::Instance()->StateName());

	TextManager::Instance()->UseFont("ubuntu", 14);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(10, 10);
	TextManager::Instance()->Render(VERSION_STR);
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
