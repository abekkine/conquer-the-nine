#include "Game.h"

#include <iostream>
#include <exception>

#include "Exception.h"
#include "GameState.h"
#include "Display.h"
#include "ScreenTestObject.h"
#include "WorldTestObject.h"
#include "GameMenu.h"
#include "PauseMenu.h"
#include "HelpPanel.h"
#include "GameSettings.h"
#include "Universe.h"
#include "Player.h"
#include "GameText.h"

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
		saveManager_ = new GameSaveManager("savegame.dat");

		GameState::Instance()->OfGame(this);
		GameState::Instance()->State(GameState::gsMENU);

		Display::Viewport v;

		// With default values (for now).
		v.type = Display::vtTopLeftOrigin;
		Display::Instance()->AddLayerViewport("text", v);

		Display::Viewport* vp;
		v.unitsPerPixel = 0.125;
		v.type = Display::vtCenterOrigin;
		vp = Display::Instance()->AddLayerViewport("game", v);

		v.unitsPerPixel = 0.005;
		v.type = Display::vtCenterOrigin;
		Display::Instance()->AddLayerViewport("test", v);

		obj = new ScreenTestObject();
		Display::Instance()->AddDisplayObject("text", obj);

		obj = new WorldTestObject();
		Display::Instance()->AddDisplayObject("test", obj);

		GameMenu* menu = new GameMenu();
		menu->SaveFileExists(saveManager_->CheckSaveData());
		Display::Instance()->AddDisplayObject("text", menu);

		obj = new HelpPanel();
		Display::Instance()->AddDisplayObject("text", obj);

		settings_ = new GameSettings();
		Display::Instance()->AddDisplayObject("text", settings_);

		Universe* u = new Universe();
		Display::Instance()->AddDisplayObject("game", u);

		Player* p = new Player();
		p->RegisterViewport(vp);
		Display::Instance()->AddDisplayObject("game", p);
		saveManager_->RegisterEntity(p);

		GameText* gt = new GameText();
		gt->RegisterPlayer(p);
		gt->RegisterUniverse(u);
		Display::Instance()->AddDisplayObject("text", gt);

		obj = new PauseMenu();
		Display::Instance()->AddDisplayObject("text", obj);

		bool fsFlag = settings_->GetFullscreenFlag();
		int w, h;
		settings_->GetWindowSize(w, h);
		Display::Instance()->FullScreen(fsFlag);
		Display::Instance()->WindowSize(w, h);
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

void Game::New()
{
	std::cout << "Game::New()" << std::endl;
	Display::Instance()->InitObjects();
}

void Game::Load()
{
	std::cout << "Game::Load()" << std::endl;
	saveManager_->Load();
}

void Game::Save()
{
	std::cout << "Game::Save()" << std::endl;
	saveManager_->Save();
}

void Game::SaveSettings()
{
	settings_->Save();
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