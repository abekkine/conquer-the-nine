#include "GameSettings.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "GameState.h"
#include "TextManager.h"
#include "Exception.h"

GameSettings::GameSettings()
	: configFile_("ct9.json")
{
	loaded_ = Load();
}


GameSettings::~GameSettings()
{
}

bool GameSettings::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsSETTINGS ||
		s == GameState::gsSAVESETTINGS)
		return false;
	else
		return true;
}

bool GameSettings::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			PrevSettingItem(); break;
		case GLFW_KEY_DOWN:
			NextSettingItem(); break;
		case GLFW_KEY_RIGHT:
			NextSettingValue(); break;
		case GLFW_KEY_LEFT:
			PrevSettingValue(); break;
		case GLFW_KEY_ENTER:
			SelectSettingItem(); break;
		}
	}

	return dispatch;
}

void GameSettings::Render()
{
	if (StateMismatch())
		return;

	SettingContainerType::const_iterator it;
	TextManager::Instance()->UseFont("ubuntu", 30);
	for (it = settingItems_.begin(); it != settingItems_.end(); ++it)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2i((*it)->x, (*it)->y);
		TextManager::Instance()->Render((*it)->label);

		if (it == selected_)
		{
			glRasterPos2i((*it)->x - 40, (*it)->y);
			TextManager::Instance()->Render(">");
		}

		// Value rendering
		ValueListType vList = (*it)->valueList;
		if (!vList.empty())
		{
			glColor3f(0.5f, 0.5f, 0.5f);
			glRasterPos2i((*it)->x + 300, (*it)->y);
			ValueListType::iterator v = (*it)->value;
			TextManager::Instance()->Render(*v);
		}
	}
}

void GameSettings::LoadItemValue(SettingItem* s)
{
	if (!loaded_)
	{
		s->value = s->valueList.begin();
		jSave_[s->name] = s->valueList[0];
	}
	else
	{
		ValueListType::iterator it;
		it = std::find(s->valueList.begin(), s->valueList.end(), jLoad_[s->name]);
		if (it != s->valueList.end())
		{
			s->value = it;
		}
		else
		{
			s->value = s->valueList.begin();
		}
	}
}

void GameSettings::Init(int w, int h)
{
	const int left = 100;
	const int step = 50;
	int top = 100;
	SettingItem* s;

	// Window Size
	s = new SettingItem();
	s->label = "Window Size";
	s->name = "wsize";
	s->valueList = ValueListType();
	s->valueList.push_back("1024x768");
	s->valueList.push_back("1280x768");
	s->valueList.push_back("1280x800");
	s->valueList.push_back("1280x1024");
	s->valueList.push_back("1366x768");
	s->valueList.push_back("1440x900");
	s->valueList.push_back("1600x900");
	s->valueList.push_back("1680x1050");
	s->valueList.push_back("1920x1080");
	s->x = left; s->y = top;
	s->targetState = GameState::gsSETTINGS;
	LoadItemValue(s);
	settingItems_.push_back(s);


	// Full Screen
	top += step;
	s = new SettingItem();
	s->label = "Fullscreen";
	s->name = "fscreen";
	s->valueList = ValueListType();
	s->valueList.push_back("On");
	s->valueList.push_back("Off");
	s->value = std::next(s->valueList.begin());
	s->x = left; s->y = top;
	s->targetState = GameState::gsSETTINGS;
	LoadItemValue(s);
	settingItems_.push_back(s);

	// Save 'Button'
	top += step;
	s = new SettingItem();
	s->label = "Save";
	s->valueList = ValueListType();
	s->value = s->valueList.end();
	s->x = left; s->y = top;
	s->targetState = GameState::gsSAVESETTINGS;
	settingItems_.push_back(s);

	// Back 'Button'
	top += step;
	s = new SettingItem();
	s->label = "Back";
	s->valueList = ValueListType();
	s->value = s->valueList.end();
	s->x = left; s->y = top;
	s->targetState = GameState::gsMENU;
	settingItems_.push_back(s);

	// No settings file, write while initiating...
	if (!loaded_)
	{
		std::fstream configFile(configFile_, std::fstream::out | std::fstream::trunc);
		configFile << jSave_.dump(4);
		configFile.close();
	}

	selected_ = settingItems_.begin();
}

bool GameSettings::Load()
{
	bool success = false;
	try
	{
		std::fstream configFile(configFile_, std::fstream::in);
		configFile >> jLoad_;
		std::cout << jLoad_["wsize"] << std::endl;
		std::cout << jLoad_["fscreen"] << std::endl;
		configFile.close();
		success = true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return success;
}

void GameSettings::Save()
{
	std::fstream configFile(configFile_, std::fstream::out | std::fstream::trunc);
	jSave_.clear();
	for (auto i = settingItems_.begin(); i != settingItems_.end(); ++i)
	{
		std::string key = (*i)->name;
		if (!key.empty())
		{
			ValueListType::iterator vit = (*i)->value;
			std::string value = *vit;
			jSave_[key] = value;
		}
	}
	configFile << jSave_.dump(4);
	configFile.close();
}

void GameSettings::SelectNextCircular()
{
	selected_ = std::next(selected_);
	if (selected_ == settingItems_.end())
	{
		selected_ = settingItems_.begin();
	}
}

void GameSettings::SelectPrevCircular()
{
	if (selected_ == settingItems_.begin())
	{
		selected_ = settingItems_.end();
		--selected_;
	}
	else
	{
		selected_ = std::prev(selected_);
	}
}

void GameSettings::NextSettingItem()
{
	SelectNextCircular();
}

void GameSettings::PrevSettingItem()
{
	SelectPrevCircular();
}

void GameSettings::SelectSettingItem()
{
	GameState::GameStateType targetState = (*selected_)->targetState;
	if (targetState != GameState::Instance()->State())
	{
		selected_ = settingItems_.begin();
		GameState::Instance()->State(targetState);
	}
}

void GameSettings::NextSettingValue()
{
	SettingItem* s = *selected_;
	if (!s->valueList.empty())
	{
		s->value = std::next(s->value);
		if (s->value == s->valueList.end())
		{
			s->value = s->valueList.begin();
		}
	}
}

void GameSettings::PrevSettingValue()
{
	SettingItem* s = *selected_;
	if (!s->valueList.empty())
	{
		if (s->value == s->valueList.begin())
		{
			s->value = s->valueList.end();
			--(s->value);
		}
		else
		{
			s->value = std::prev(s->value);
		}
	}
}

void GameSettings::GetWindowSize(int& width, int& height)
{
	std::string windowSize = jLoad_["wsize"];
	std::istringstream ws (windowSize);
	std::string s;

	std::getline(ws, s, 'x');
	width = std::stoi(s, nullptr, 0);

	std::getline(ws, s, 'x');
	height = std::stoi(s, nullptr, 0);
}

bool GameSettings::GetFullscreenFlag()
{
	bool fs = false;
	std::string fullScreen = jLoad_["fscreen"];

	if (fullScreen == "On")
	{
		fs = true;
	}

	return fs;
}
