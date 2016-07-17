#ifndef GAME_SETTINGS_H_
#define GAME_SETTINGS_H_

#include <string>
#include <vector>

// UPDATE:json
#include "json.hpp"
using json = nlohmann::json;

#include "DisplayObjectInterface.h"
#include "GameState.h"

class GameSettings : public DisplayObjectInterface
{
private:
	typedef std::vector<std::string> ValueListType;
	struct SettingItem {
		std::string label;
		std::string name;
		ValueListType::iterator value;
		ValueListType valueList;
		int x, y;
		GameState::GameStateType targetState;
	};

	typedef std::vector<SettingItem*> SettingContainerType;
	SettingContainerType settingItems_;
	SettingContainerType::iterator selected_;
	const std::string configFile_;
	bool loaded_;
	json jSave_;
	json jLoad_;

public:
	GameSettings();
	~GameSettings();
	bool StateMismatch();

	virtual bool KeyEvent(int key, int scancode, int action, int mods);
	virtual void MouseButtonEvent(int button, int action, int mods) {}
	virtual void CursorPositionEvent(double x, double y) {}
	virtual void Render();
	virtual void Init();
	bool Load();
	void Save();
	void GetWindowSize(int& width, int& height);
	bool GetFullscreenFlag();

private:
	void LoadItemValue(SettingItem* s);
	void SelectNextCircular();
	void SelectPrevCircular();
	void NextSettingItem();
	void PrevSettingItem();
	void SelectSettingItem();
	void NextSettingValue();
	void PrevSettingValue();
};

#endif // GAME_SETTINGS_H_
