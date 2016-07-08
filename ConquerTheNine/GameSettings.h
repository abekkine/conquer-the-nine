#ifndef GAME_SETTINGS_H_
#define GAME_SETTINGS_H_

#include <string>
#include <vector>

#include "DisplayObjectInterface.h"
#include "GameState.h"

class GameSettings : public DisplayObjectInterface
{
private:
	typedef struct {
		std::string label;
		std::string value;
		int x, y;
		GameState::GameStateType targetState;
	} SettingItemType;

	typedef std::vector<SettingItemType> SettingContainerType;
	SettingContainerType settingItems_;
	SettingContainerType::iterator selected_;

public:
	GameSettings();
	~GameSettings();
	bool StateMismatch();

	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void RenderToWorld() {}
	virtual void RenderToScreen();
	virtual void Init();

private:
	void SelectNextCircular();
	void SelectPrevCircular();
	void NextSettingItem();
	void PrevSettingItem();
	void SelectSettingItem();
	void NextSettingValue();
	void PrevSettingValue();
};

#endif // GAME_SETTINGS_H_
