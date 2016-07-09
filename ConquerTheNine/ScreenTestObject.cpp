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

void ScreenTestObject::Init()
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

void ScreenTestObject::RenderToScreen()
{
	if (StateMismatch())
		return;

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(300, 50);
	TextManager::Instance()->UseFont("anonym", 20);
	TextManager::Instance()->Render("Anonymous Pro, 20");

	glRasterPos2i(300, 100);
	TextManager::Instance()->UseFont("droid", 30);
	TextManager::Instance()->Render("Droid Sans Mono, 30");

	glRasterPos2i(300, 150);
	TextManager::Instance()->UseFont("ubuntu", 40);
	TextManager::Instance()->Render("Ubuntu Mono, 40");
}