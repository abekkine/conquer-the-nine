#ifndef GAME_TEXT_H_
#define GAME_TEXT_H_

#include "DisplayObjectInterface.h"

#include "Player.h"
#include "Universe.h"

#include <vector>

class GameText : public DisplayObjectInterface
{
private:
	Universe* universe_;
	Player* player_;
	std::vector<double> bodyLocations_;
	double barMin_;
	double barMax_;
	int scrW_;
	int scrH_;
	double xLeft_;
	double xRight_;
	double xSpan_;
	double xMargin_;
public:
	GameText();
	~GameText();

	bool StateMismatch();
	virtual bool KeyEvent(int key, int scancode, int action, int mods) { return false; }
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	void RegisterPlayer(Player* p);
	void RegisterUniverse(Universe* u);

private:
	void RenderPlayerPos();
	void RenderNeighbors();
	void RenderLocationBar();
};

#endif // GAME_TEXT_H_
