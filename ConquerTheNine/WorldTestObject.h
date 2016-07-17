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

	virtual bool KeyEvent(int key, int scancode, int action, int mods) { return false; }
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	virtual bool StateMismatch();
};

#endif // WORLD_TEST_OBJECT_H_
