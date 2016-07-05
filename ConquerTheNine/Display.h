#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GLFW/glfw3.h>

#include <string>

class Display
{
private:
	static Display* instance_;
	GLFWwindow* window_;

private:
	Display();
	// Static callback methods, and their processor methods.
	static void errorCallback(int error, const char* description);
	static void resizeCallback(GLFWwindow* w, int width, int height);
	static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);

	void RenderWorldContents();
	void RenderScreenContents();

public:
	static Display* Instance();
	~Display();

	void InitDisplay();
	void Run();

	void ErrorHandler(int error, std::string description);
	void ResizeHandler(GLFWwindow* w, int width, int height);
	void KeyHandler(GLFWwindow* w, int key, int scancode, int action, int mods);
};

#endif // DISPLAY_H_


