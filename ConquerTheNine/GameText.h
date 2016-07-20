#ifndef GAME_TEXT_H_
#define GAME_TEXT_H_

#include "DisplayObjectInterface.h"

#include "Player.h"
#include "Universe.h"

class GameText : public DisplayObjectInterface
{
private:
	Universe* universe_;
	Player* player_;
public:
	GameText();
	~GameText();

	bool StateMismatch();
	virtual bool KeyEvent(int key, int scancode, int action, int mods) { return false; }
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init(int w, int h);
	void RegisterPlayer(Player* p) { player_ = p; }
	void RegisterUniverse(Universe* u) { universe_ = u; }
};

#endif // GAME_TEXT_H_
