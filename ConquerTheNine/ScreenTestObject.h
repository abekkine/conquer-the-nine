#ifndef SCREEN_TEST_OBJECT_H_
#define SCREEN_TEST_OBJECT_H_

#include "DisplayObjectInterface.h"

class ScreenTestObject : public DisplayObjectInterface
{
public:
	ScreenTestObject();
	~ScreenTestObject();

	virtual bool KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	virtual bool StateMismatch();
};

#endif // SCREEN_TEST_OBJECT_H_
