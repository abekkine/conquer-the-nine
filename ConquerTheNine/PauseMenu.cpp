#include "PauseMenu.h"

#include <GLFW/glfw3.h>

#include "TextManager.h"

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

bool PauseMenu::CanDispatch()
{
	return GameState::gsPAUSE == GameState::Instance()->State();
}

bool PauseMenu::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			selected_ = resumeMenuItem_;
			dispatch = CanDispatch();
			SelectMenuItem();
			break;
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

void PauseMenu::FrameVertices()
{
	glVertex2i(x_, y_);
	glVertex2i(x_ + width_, y_);
	glVertex2i(x_ + width_, y_ + height_);
	glVertex2i(x_, y_ + height_);
}

void PauseMenu::RenderFrame()
{
	glColor4f(0.2, 0.2, 0.8, 0.8);
	glBegin(GL_QUADS);
	FrameVertices();
	glEnd();

	glColor4f(0.6, 0.6, 1.0, 0.4);
	glBegin(GL_LINE_LOOP);
	FrameVertices();
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

void PauseMenu::Init(int w, int h)
{
	int left;
	const int step = 50;
	int top;

	x_ = 150; 
	y_ = 150;
	width_ = 320;
	height_ = 130;

	left = x_ + 50;
	top = y_ + 50;

	menuItems_.push_back({ std::string("Resume"), left, top, false, GameState::gsPLAY });
	top += step;
	menuItems_.push_back({ std::string("Save & Quit"), left, top, false, GameState::gsSAVEGAME });

	selected_ = menuItems_.begin();
	resumeMenuItem_ = selected_;
	flagPauseState_ = 0;
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
