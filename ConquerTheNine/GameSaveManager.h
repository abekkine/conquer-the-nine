#ifndef GAME_SAVE_MANAGER_H_
#define GAME_SAVE_MANAGER_H_

#include <vector>

#include "SaveableInterface.h"

class GameSaveManager
{
private:
	typedef std::vector<SaveableInterface*> SaveableContainerType;
	SaveableContainerType saveables_;
	std::string saveFile_;
public:
	GameSaveManager(std::string savefile);
	~GameSaveManager();
	void RegisterEntity(SaveableInterface* entity);
	bool CheckSaveData();
	void Load();
	void Save();
};

#endif // GAME_SAVE_MANAGER_H_


