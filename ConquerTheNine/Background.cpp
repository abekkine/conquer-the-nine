#include "Background.h"

#include <GLFW/glfw3.h>

#include "GameState.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Render()
{
	if (StateMismatch())
		return;

	glPushMatrix();

	glPointSize(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (auto it = stars_.begin(); it != stars_.end(); ++it)
	{
		glVertex2d((*it).x, (*it).y);
	}
	glEnd();

	glPopMatrix();
}

void Background::Init(int w, int h)
{
	BGStar bgStar;
	for (int i = 0; i < 100; i++)
	{
		bgStar.x = 0.0;
		bgStar.y = 0.0;
		stars_.push_back(bgStar);
	}
}

bool Background::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();
	if (s == GameState::gsPLAY || s == GameState::gsPAUSE)
		return false;
	else
		return true;
}
