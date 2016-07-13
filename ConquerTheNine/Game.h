#ifndef GAME_H_
#define GAME_H_

#include "GameSaveManager.h"
#include "GameSettings.h"

class Game
{
private:
	GameSaveManager* saveManager_;
	GameSettings* settings_;
public:
	Game();
	virtual ~Game();
	void Init();
	void Exit();
	void Run();
	void New();
	void Load();
	void Save();
	void SaveSettings();
};

#endif // GAME_H_


