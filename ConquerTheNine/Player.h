#ifndef PLAYER_H_
#define PLAYER_H_

#include "DisplayObjectInterface.h"

#include "Display.h"

class Player : public DisplayObjectInterface
{
private:
	double x_;
	double y_;
	double vx_;
	double vy_;
	Display::Viewport* viewport_;
	double vpHalfWidth_;
	double vpHalfHeight_;

public:
	Player();
	~Player();

	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();
	virtual bool StateMismatch();
	void RegisterViewport(Display::Viewport* vp);
	bool IsPaused();
};

#endif // PLAYER_H_
