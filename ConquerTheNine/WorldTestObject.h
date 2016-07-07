#ifndef WORLD_TEST_OBJECT_H_
#define WORLD_TEST_OBJECT_H_

#include "DisplayObjectInterface.h"

class WorldTestObject : public DisplayObjectInterface
{
private:
	double a;
public:
	WorldTestObject();
	~WorldTestObject();

	virtual void KeyEvent(int key, int scancode, int action, int mods) {}
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void RenderToWorld();
	virtual void RenderToScreen() {}
	virtual void Init();
};

#endif // WORLD_TEST_OBJECT_H_
