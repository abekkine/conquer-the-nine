#include "PauseMenu.h"

#include <GLFW/glfw3.h>

#include "TextManager.h"
#include "Exception.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::~PauseMenu()
{
}

bool PauseMenu::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsPAUSE)
		return false;
	else
		return true;
}

void PauseMenu::KeyEvent(int key, int scancode, int action, int mods)
{
	if (StateMismatch())
		return;

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

void PauseMenu::RenderFrame()
{
	int x, y, w, h;

	x = 140; y = 420;
	w = 320; h = 130;

	glColor4f(0.2, 0.2, 0.8, 0.8);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();

	glColor4f(0.6, 0.6, 1.0, 0.4);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x, y);
	glVertex2i(x + w, y);
	glVertex2i(x + w, y + h);
	glVertex2i(x, y + h);
	glEnd();

}

void PauseMenu::RenderMenuItems()
{
	MenuContainerType::const_iterator it;
	TextManager::Instance()->UseFont("ubuntu", 40);
	for (it = menuItems_.begin(); it != menuItems_.end(); ++it)
	{
		if ((*it).disabled)
		{
			glColor3f(0.5f, 0.5f, 0.5f);
		}
		else
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glRasterPos2i((*it).x, (*it).y);
		TextManager::Instance()->Render((*it).label);
		if (it == selected_)
		{
			glRasterPos2i((*it).x - 40, (*it).y);
			TextManager::Instance()->Render(">");
		}
	}
}

void PauseMenu::Render()
{
	if (StateMismatch())
		return;

	RenderFrame();
	RenderMenuItems();
}

void PauseMenu::Init()
{
	const int left = 200;
	const int step = 50;
	int y = 500;

	menuItems_.push_back({ std::string("Resume"), left, y, false, GameState::gsPLAY });
	y -= step;
	menuItems_.push_back({ std::string("Save & Quit"), left, y, false, GameState::gsSAVEGAME });

	selected_ = menuItems_.begin();
}

void PauseMenu::SelectNextCircular()
{
	selected_ = std::next(selected_);
	if (selected_ == menuItems_.end())
	{
		selected_ = menuItems_.begin();
	}
}

void PauseMenu::SelectPrevCircular()
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

void PauseMenu::NextMenuItem()
{
	SelectNextCircular();
	if ((*selected_).disabled)
	{
		SelectNextCircular();
	}
}

void PauseMenu::PrevMenuItem()
{
	SelectPrevCircular();
	if ((*selected_).disabled)
	{
		SelectPrevCircular();
	}
}

void PauseMenu::SelectMenuItem()
{
	GameState::Instance()->State((*selected_).targetState);
}
