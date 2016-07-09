#ifndef DISPLAY_OBJECT_INTERFACE_H_
#define DISPLAY_OBJECT_INTERFACE_H_

class DisplayObjectInterface
{
public:
	virtual void KeyEvent(int key, int scancode, int action, int mods) = 0;
	virtual void MouseButtonEvent(int button, int action, int mods) = 0;
	virtual void CursorPositionEvent(double x, double y) = 0;
	virtual void Init() = 0;
	virtual void RenderToWorld() = 0;
	virtual void RenderToScreen() = 0;
	virtual bool StateMismatch() = 0;
};

#endif // DISPLAY_OBJECT_INTERFACE_H_

