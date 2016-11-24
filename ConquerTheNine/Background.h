#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <vector>

#include "DisplayObjectInterface.h"

class Background : public DisplayObjectInterface
{
public: // Methods
	Background();
	~Background();
	virtual bool KeyEvent(int key, int scancode, int action, int mods) { return false; }
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	virtual bool StateMismatch();

private: // Methods

private: // Members
	struct BGStar {
		double x, y;
	};
	std::vector<BGStar> stars_;
};

#endif // BACKGROUND_H_
