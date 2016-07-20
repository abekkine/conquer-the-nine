#include "GameText.h"

#include "TextManager.h"
#include "GameState.h"

GameText::GameText()
{
}


GameText::~GameText()
{
}

void GameText::Init(int w, int h)
{

}

bool GameText::StateMismatch()
{
	GameState::GameStateType s = GameState::Instance()->State();

	if (s == GameState::gsPLAY || s == GameState::gsPAUSE)
		return false;
	else
		return true;
}

void GameText::Render()
{
	if (StateMismatch())
		return;

	double px, py;
	player_->GetPosition(px, py);

	TextManager::Instance()->UseFont("ubuntu", 14);
	std::string xpos = std::to_string(px);
	glColor3f(1.0, 0.5, 0.5);
	glRasterPos2i(200, 200);
	TextManager::Instance()->Render(xpos);
}
