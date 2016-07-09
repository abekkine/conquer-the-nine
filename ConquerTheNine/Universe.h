#ifndef UNIVERSE_H_
#define UNIVERSE_H_

#include <random>
#include <vector>

#include "DisplayObjectInterface.h"

class Universe : public DisplayObjectInterface
{
private:
	std::default_random_engine generator_;
	struct DummyObject {
		double x, y;
		double size;
		double shade;
	};
	typedef std::vector<DummyObject*> DummyContainerType;
	DummyContainerType objects_;

public:
	Universe();
	~Universe();

	virtual void KeyEvent(int key, int scancode, int action, int mods) {}
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();
	virtual bool StateMismatch();

private:
	double RandomBetween(double min, double max);
};

#endif // UNIVERSE_H_
