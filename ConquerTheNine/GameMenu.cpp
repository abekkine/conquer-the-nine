#include "GameMenu.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "GameState.h"
#include "TextManager.h"
#include "Exception.h"

GameMenu::GameMenu()
{
}

GameMenu::~GameMenu()
{
}

void GameMenu::KeyEvent(int key, int scancode, int action, int mods)
{
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
}

void GameMenu::MouseButtonEvent(int button, int action, int mods)
{
}

void GameMenu::CursorPositionEvent(double x, double y)
{
}

void GameMenu::RenderToScreen()
{
	if (GameState::gsMENU != GameState::Instance()->State())
	{
		return;
	}

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

void GameMenu::Init()
{
	const int menuLeft = 100;
	const int menuStep = 50;
	int menuY = 700;

	menuItems_.push_back({ std::string("New Game"), menuLeft, menuY, false, GameState::gsINITGAME });
	menuY -= menuStep;
	menuItems_.push_back({ std::string("Continue"), menuLeft, menuY, true, GameState::gsLOADGAME });
	menuY -= menuStep;
	menuItems_.push_back({ std::string("Settings"), menuLeft, menuY, false, GameState::gsSETTINGS });
	menuY -= menuStep;
	menuItems_.push_back({ std::string("Quit"), menuLeft, menuY, false, GameState::gsQUIT });

	selected_ = menuItems_.begin();
	if (selected_ == menuItems_.end())
	{
		throw Exception("Unable to find default menu item!");
	}
}

void GameMenu::SelectNextCircular()
{
	selected_ = std::next(selected_);
	if (selected_ == menuItems_.end()) {
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
