#ifndef PLAYER_H_
#define PLAYER_H_

#include "DisplayObjectInterface.h"
#include "SaveableInterface.h"

#include "Display.h"

class Player : public DisplayObjectInterface, public SaveableInterface
{
private:
	double x_;
	double y_;
	double vx_;
	double vy_;
	Display::Viewport* viewport_;
	double vpHalfWidth_;
	double vpHalfHeight_;
private:
	struct {
		double x;
		double y;
	} save_;

public:
	Player();
	~Player();

	virtual bool KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();
	virtual bool StateMismatch();
	bool CanDispatch();
	void RegisterViewport(Display::Viewport* vp);
	bool IsPaused();
	// Saveable interface
	void Save(std::fstream& s);
	void Load(std::fstream& s);
};

#endif // PLAYER_H_
