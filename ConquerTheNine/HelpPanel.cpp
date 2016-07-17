#include "HelpPanel.h"

#include <GLFW/glfw3.h>

#include "TextManager.h"
#include "GameState.h"

HelpPanel::HelpPanel()
{
}

HelpPanel::~HelpPanel()
{
}

bool HelpPanel::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsPLAY)
		return false;
	else
		return true;
}

bool HelpPanel::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			flagShowHelp_ = 0; break;
		case GLFW_KEY_H:
			flagShowHelp_ ^= 1; break;
		}
	}

	return dispatch;
}

void HelpPanel::Render()
{
	if (StateMismatch())
		return;

	if (!flagShowHelp_)
		return;

	RenderFrame();
	RenderHelpItems();
}

void HelpPanel::Init(int w, int h)
{
	flagShowHelp_ = true;
	w_ = 350; h_ = 130;
	x_ = w - w_ - 50; y_ = h - h_ - 50;
}

void HelpPanel::FrameVertices()
{
	glVertex2i(x_, y_);
	glVertex2i(x_ + w_, y_);
	glVertex2i(x_ + w_, y_ + h_);
	glVertex2i(x_, y_ + h_);
}

void HelpPanel::RenderFrame()
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

void HelpPanel::RenderHelpItems()
{
	int m = 20;
	int cy = 10;
	TextManager::Instance()->UseFont("ubuntu", 16);
	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Help");
	cy += m;

	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("-------------------------------");
	cy += m;

	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Press 'h' for this panel");
	cy += m;

	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Press 'p' to pause");
	cy += m;

	glRasterPos2i(x_ + m,  y_ + m + cy);
	TextManager::Instance()->Render("Use cursor keys to move player.");
	cy += m;
}

