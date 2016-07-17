#ifndef DISPLAY_OBJECT_INTERFACE_H_
#define DISPLAY_OBJECT_INTERFACE_H_

class DisplayObjectInterface
{
public:
	virtual bool KeyEvent(int key, int scancode, int action, int mods) = 0;
	virtual void MouseButtonEvent(int button, int action, int mods) = 0;
	virtual void CursorPositionEvent(double x, double y) = 0;
	virtual void Init(int w, int h) = 0;
	virtual void Render() = 0;
	virtual bool StateMismatch() = 0;
};

#endif // DISPLAY_OBJECT_INTERFACE_H_

