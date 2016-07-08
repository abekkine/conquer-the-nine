#include "Game.h"

#include <iostream>
#include <exception>

#include "Exception.h"
#include "GameState.h"
#include "Display.h"
#include "ScreenTestObject.h"
#include "WorldTestObject.h"
#include "GameMenu.h"
#include "GameSettings.h"

Game::Game()
{
	std::cout << "Game::Game()" << std::endl;
}

Game::~Game()
{
	std::cout << "Game::~Game()" << std::endl;
}

void Game::Init()
{
	std::cout << "Game::Init()" << std::endl;
	DisplayObjectInterface* obj;

	try
	{
		GameState::Instance()->OfGame(this);
		GameState::Instance()->State(GameState::gsMENU);

		obj = new ScreenTestObject();
		Display::Instance()->AddDisplayObject(obj);

		obj = new WorldTestObject();
		Display::Instance()->AddDisplayObject(obj);

		obj = new GameMenu();
		Display::Instance()->AddDisplayObject(obj);

		obj = new GameSettings();
		Display::Instance()->AddDisplayObject(obj);

		Display::Instance()->Init();
	}
	catch (Exception& e)
	{
		std::cout << __FILE__ << ":" << __LINE__ << " : ";
		throw(e);
	}
}

void Game::Exit()
{
	std::cout << "Game::Exit()" << std::endl;
}

void Game::Load()
{
	std::cout << "Game::Load()" << std::endl;
}

void Game::Save()
{
	std::cout << "Game::Save()" << std::endl;
}

void Game::Run()
{
	std::cout << "Game::Run()" << std::endl;

	try
	{
		Display::Instance()->Run();
	}
	catch (Exception& e) {
		std::cout << __FILE__ << ":" << __LINE__ << " : ";
		throw(e);
	}
}