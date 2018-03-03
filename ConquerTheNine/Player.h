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
    double fx_;
    double fy_;
	double ax_;
	double ay_;
    double mass_;
	Display::Viewport* viewport_;
	double vpHalfWidth_;
	double vpHalfHeight_;
	double prevTime_;
	double curTime_;
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
	virtual void Init(int w, int h);
	virtual bool StateMismatch();
	bool CanDispatch();
	void RegisterViewport(Display::Viewport* vp);
	bool IsPaused();
	// Saveable interface
	void Save(std::fstream& s);
	void Load(std::fstream& s);
	void GetPosition(double& x, double& y) { x = x_; y = y_; }
	double GetSpeed() { return abs(vx_); }
	void UpdatePhysics();
    void SetRelativisticViewport(double lf);
};

#endif // PLAYER_H_
