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
		glRasterPos2i((*it).x, (*it).y);
		TextManager::Instance()->Render((*it).label);
		glColor3f(0.5f, 0.5f, 0.5f);
		glRasterPos2i((*it).x + 300, (*it).y);
		TextManager::Instance()->Render((*it).value);
		if (it == selected_)
		{
			glRasterPos2i((*it).x - 40, (*it).y);
			TextManager::Instance()->Render(">");
		}
	}
}

void GameSettings::Init()
{
	const int left = 100;
	const int step = 50;
	int y = 700;

	settingItems_.push_back({
		"Window Size", "800",
		left, y,
		GameState::gsSETTINGS
	});
	y -= step;
	settingItems_.push_back({
		"Save", "",
		left, y,
		GameState::gsSAVESETTINGS
	});
	y -= step;
	settingItems_.push_back({
		"Back", "",
		left, y,
		GameState::gsMENU
	});

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
	GameState::GameStateType targetState = (*selected_).targetState;
	if (targetState != GameState::Instance()->State())
	{
		selected_ = settingItems_.begin();
		GameState::Instance()->State(targetState);
	}
}

void GameSettings::NextSettingValue()
{

}

void GameSettings::PrevSettingValue()
{

}
