#ifndef PAUSE_MENU_H_
#define PAUSE_MENU_H_

#include <string>
#include <vector>

#include "DisplayObjectInterface.h"
#include "GameState.h"

class PauseMenu : public DisplayObjectInterface
{
private:
	typedef struct {
		std::string label;
		int x, y;
		bool disabled;
		GameState::GameStateType targetState;
	} MenuItemType;

	typedef std::vector<MenuItemType> MenuContainerType;
	MenuContainerType menuItems_;
	MenuContainerType::iterator selected_;

public:
	PauseMenu();
	~PauseMenu();

	bool StateMismatch();
	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();

private:
	void SelectNextCircular();
	void SelectPrevCircular();
	void NextMenuItem();
	void PrevMenuItem();
	void SelectMenuItem();
	void RenderFrame();
	void RenderMenuItems();
};

#endif // PAUSE_MENU_H_
