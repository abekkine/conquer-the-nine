#include "GameSettings.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "GameState.h"
#include "TextManager.h"
#include "Exception.h"

GameSettings::GameSettings()
{
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

void GameSettings::KeyEvent(int key, int scancode, int action, int mods)
{
	if (StateMismatch())
		return;

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
}

void GameSettings::RenderToScreen()
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

void GameSettings::Init()
{
	const int left = 100;
	const int step = 50;
	int y = 700;
	SettingItem* s;

	// Window Size
	s = new SettingItem();
	s->label = "Window Size";
	s->valueList = ValueListType();
	s->valueList.push_back("500");
	s->valueList.push_back("640");
	s->valueList.push_back("800");
	s->valueList.push_back("960");
	s->value = s->valueList.begin();
	s->x = left; s->y = y;
	s->targetState = GameState::gsSETTINGS;
	settingItems_.push_back(s);

	// Full Screen
	y -= step;
	s = new SettingItem();
	s->label = "Fullscreen";
	s->valueList = ValueListType();
	s->valueList.push_back("On");
	s->valueList.push_back("Off");
	s->value = std::next(s->valueList.begin());
	s->x = left; s->y = y;
	s->targetState = GameState::gsSETTINGS;
	settingItems_.push_back(s);

	// Save 'Button'
	y -= step;
	s = new SettingItem();
	s->label = "Save";
	s->valueList = ValueListType();
	s->value = s->valueList.end();
	s->x = left; s->y = y;
	s->targetState = GameState::gsSAVESETTINGS;
	settingItems_.push_back(s);

	// Back 'Button'
	y -= step;
	s = new SettingItem();
	s->label = "Back";
	s->valueList = ValueListType();
	s->value = s->valueList.end();
	s->x = left; s->y = y;
	s->targetState = GameState::gsMENU;
	settingItems_.push_back(s);

	selected_ = settingItems_.begin();
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
