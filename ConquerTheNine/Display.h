#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "DisplayObjectInterface.h"

class Display
{
private:
	static Display* instance_;
	GLFWwindow* window_;
	typedef	std::vector<DisplayObjectInterface*> ObjContainerType;
	ObjContainerType objects_;

private:
	Display();
	// Static callback methods, and their processor methods.
	static void errorCallback(int error, const char* description);
	static void resizeCallback(GLFWwindow* w, int width, int height);
	static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* w, int button, int action, int mods);
	static void cursorPositionCallback(GLFWwindow* w, double x, double y);
	static void scrollCallback(GLFWwindow* w, double x, double y);

	void InitDisplay();
	void InitObjects();
	void RenderWorldObjects();
	void RenderWorldContents();
	void RenderScreenObjects();
	void RenderScreenContents();

public:
	static Display* Instance();
	~Display();

	void AddDisplayObject(DisplayObjectInterface* obj);
	void Init();
	void Run();

	// Handler methods
	void ErrorHandler(int error, std::string description);
	void ResizeHandler(GLFWwindow* w, int width, int height);
	void KeyHandler(GLFWwindow* w, int key, int scancode, int action, int mods);
	void CursorPositionHandler(GLFWwindow* w, double x, double y);
	void MouseButtonHandler(GLFWwindow* w, int button, int action, int mods);
	void MouseScrollHandler(GLFWwindow* w, double x, double y);
};

#endif // DISPLAY_H_


