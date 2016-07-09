#ifndef GAME_SETTINGS_H_
#define GAME_SETTINGS_H_

#include <string>
#include <vector>

#include "DisplayObjectInterface.h"
#include "GameState.h"

class GameSettings : public DisplayObjectInterface
{
private:
	typedef std::vector<std::string> ValueListType;
	struct SettingItem {
		std::string label;
		ValueListType::iterator value;
		ValueListType valueList;
		int x, y;
		GameState::GameStateType targetState;
	};

	typedef std::vector<SettingItem*> SettingContainerType;
	SettingContainerType settingItems_;
	SettingContainerType::iterator selected_;

public:
	GameSettings();
	~GameSettings();
	bool StateMismatch();

	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
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
