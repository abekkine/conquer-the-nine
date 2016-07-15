#ifndef HELP_PANEL_H_
#define HELP_PANEL_H_

#include "DisplayObjectInterface.h"

class HelpPanel : public DisplayObjectInterface
{
private:
	unsigned char flagShowHelp_;
	int x_;
	int y_;
	int w_;
	int h_;

public:
	HelpPanel();
	~HelpPanel();

	bool StateMismatch();
	virtual bool KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();

private:
	void RenderFrame();
	void RenderHelpItems();
	void FrameVertices();
};

#endif // HELP_PANEL_H_
