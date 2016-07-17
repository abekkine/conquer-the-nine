#include "GameMenu.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "TextManager.h"
#include "Exception.h"

GameMenu::GameMenu()
{
	saveFileExists_ = false;
}

GameMenu::~GameMenu()
{
}

bool GameMenu::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsMENU)
		return false;
	else
		return true;
}

void GameMenu::SaveFileExists(bool value)
{
	saveFileExists_ = value;
}

bool GameMenu::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			PrevMenuItem(); break;
		case GLFW_KEY_DOWN:
			NextMenuItem(); break;
		case GLFW_KEY_ENTER:
		case GLFW_KEY_SPACE:
			SelectMenuItem(); break;
		}
	}

	return dispatch;
}

void GameMenu::Render()
{
	if (StateMismatch())
		return;

	MenuContainerType::const_iterator it;
	TextManager::Instance()->UseFont("ubuntu", 40);
	for (it = menuItems_.begin(); it != menuItems_.end(); ++it)
	{
		if ( (*it).disabled )
		{
			glColor3f(0.5f, 0.5f, 0.5f);
		}
		else 
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glRasterPos2i( (*it).x, (*it).y);
		TextManager::Instance()->Render( (*it).label );
		if (it == selected_)
		{
			glRasterPos2i( (*it).x - 40, (*it).y);
			TextManager::Instance()->Render(">");
		}
	}
}

void GameMenu::Init(int w, int h)
{
	const int left = 100;
	const int step = 50;
	int y = 700;

	menuItems_.push_back({ std::string("New Game"), left, y, false, GameState::gsINITGAME });
	y -= step;
	menuItems_.push_back({ std::string("Continue"), left, y, !saveFileExists_, GameState::gsLOADGAME });
	y -= step;
	menuItems_.push_back({ std::string("Settings"), left, y, false, GameState::gsSETTINGS });
	y -= step;
	menuItems_.push_back({ std::string("Test"), left, y, false, GameState::gsTEST });
	y -= step;
	menuItems_.push_back({ std::string("Quit"), left, y, false, GameState::gsQUIT });

	selected_ = menuItems_.begin();
}

void GameMenu::SelectNextCircular()
{
	selected_ = std::next(selected_);
	if (selected_ == menuItems_.end())
	{
		selected_ = menuItems_.begin();
	}
}

void GameMenu::SelectPrevCircular()
{
	if (selected_ == menuItems_.begin())
	{
		selected_ = menuItems_.end();
		--selected_;
	}
	else
	{
		selected_ = std::prev(selected_);
	}
}

void GameMenu::NextMenuItem()
{
	std::cout << "GameMenu::NextMenuItem()" << std::endl;

	SelectNextCircular();
	if ( (*selected_).disabled)
	{
		SelectNextCircular();
	}
}

void GameMenu::PrevMenuItem()
{
	std::cout << "GameMenu::PrevMenuItem()" << std::endl;

	SelectPrevCircular();
	if ((*selected_).disabled)
	{
		SelectPrevCircular();
	}
}

void GameMenu::SelectMenuItem()
{
	std::cout << "GameMenu::SelectMenuItem()" << std::endl;
	GameState::Instance()->State((*selected_).targetState);
}
