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

void HelpPanel::KeyEvent(int key, int scancode, int action, int mods)
{
	if (StateMismatch())
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_H:
			flagShowHelp_ ^= 1; break;
		}
	}
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

void HelpPanel::Init()
{
	flagShowHelp_ = true;
	x_ = 200; y_ = 150;
	w_ = 350; h_ = 130;
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
	int cy = 0;
	TextManager::Instance()->UseFont("ubuntu", 16);
	glColor3f(1.0, 1.0, 1.0);

	glRasterPos2i(x_ + m,  y_ + m + cy);
	TextManager::Instance()->Render("Use cursor keys to move player.");

	cy += 20;
	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Press 'p' to pause");

	cy += 20;
	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Press 'h' for this panel");

	cy += 20;
	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("-------------------------------");

	cy += 20;
	glRasterPos2i(x_ + m, y_ + m + cy);
	TextManager::Instance()->Render("Help");
}

