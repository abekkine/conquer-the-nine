#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <map>

#include "DisplayObjectInterface.h"

class Display
{
public:
	enum ViewportType {
		vtTopLeftOrigin,
		vtBottomLeftOrigin,
		vtCenterOrigin
	};
	struct Viewport {
		ViewportType type;
		double unitsPerPixel;
		double widthFactor;
		double cx, cy;
		double left, right, bottom, top;
		Viewport() {
			type = vtBottomLeftOrigin;
			unitsPerPixel = 1.0;
			widthFactor = 1.0;
			cx = cy = 0.0;
			left = bottom = -1.0; right = top = 1.0;
		}
	};
private:
	static Display* instance_;
	GLFWwindow* window_;
	int scrWidth_;
	int scrHeight_;
	typedef	std::vector<DisplayObjectInterface*> ObjContainerType;
	struct LayerObject {
		Viewport viewport;
		ObjContainerType objects;
	};
	typedef std::map<std::string, LayerObject> LayerContainerType;
	LayerContainerType layers_;
	bool fullScreen_;
	int reqWidth_;
	int reqHeight_;

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
	void RenderContents();
	void RenderObjects();
	void RenderState();
	void UpdateViewport(Viewport& vp);

public:
	static Display* Instance();
	~Display();

	Viewport* AddLayerViewport(std::string layer, Viewport viewport);
	void AddDisplayObject(std::string layer, DisplayObjectInterface* obj);

	void FullScreen(bool value);
	void WindowSize(int w, int h);

	void Init();
	void InitObjects();
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
