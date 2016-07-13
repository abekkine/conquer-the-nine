#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <string>

class Game;

class GameState
{
public:
	typedef enum {
		gsNONE,
		gsMENU,
		gsINITGAME,
		gsLOADGAME,
		gsSAVEGAME,
		gsPLAY,
		gsPAUSE,
		gsSETTINGS,
		gsSAVESETTINGS,
		gsQUIT,
		gsTEST
	} GameStateType;

private:
	static GameState* instance_;
	GameStateType state_;
	Game* game_;

	GameState();
	void PreProcess();
	void PostProcess();

public:
	static GameState* Instance();
	~GameState();
	void OfGame(Game* game);
	GameStateType State();
	void State(GameStateType state);
	std::string StateName();
};

#endif // GAME_STATE_H_
