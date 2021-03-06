#include "ScreenTestObject.h"

#include <iostream>

#include <GLFW/glfw3.h>

#include "GameState.h"
#include "TextManager.h"

ScreenTestObject::ScreenTestObject()
{
}

ScreenTestObject::~ScreenTestObject()
{
}

bool ScreenTestObject::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();
	if (s == GameState::gsTEST)
		return false;
	else
		return true;
}

void ScreenTestObject::Init(int w, int h)
{
	try {
		TextManager::Instance()->AddFont("ubuntu", "c:/source/fonts/ubuntumono/ubuntumono-r.ttf");
		TextManager::Instance()->AddFont("droid", "c:/source/fonts/droidsansmono/droidsansmono.ttf");
		TextManager::Instance()->AddFont("anonym", "c:/source/fonts/anonymouspro/anonymous_pro.ttf");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	TextManager::Instance()->Init();
}

bool ScreenTestObject::KeyEvent(int key, int scancode, int action, int mods)
{
	bool dispatch = false;

	if (StateMismatch())
		return dispatch;

	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
	{
		GameState::Instance()->State(GameState::gsMENU);
		dispatch = true;
	}

	return dispatch;
}

void ScreenTestObject::Render()
{
	if (StateMismatch())
		return;

	int left = 100;
	int top = 100;
	int step = 50;

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(left, top += step);
	TextManager::Instance()->UseFont("anonym", 20);
	TextManager::Instance()->Render("Anonymous Pro, 20");

	glRasterPos2i(left, top += step);
	TextManager::Instance()->UseFont("droid", 30);
	TextManager::Instance()->Render("Droid Sans Mono, 30");

	glRasterPos2i(left, top += step);
	TextManager::Instance()->UseFont("ubuntu", 40);
	TextManager::Instance()->Render("Ubuntu Mono, 40");
}