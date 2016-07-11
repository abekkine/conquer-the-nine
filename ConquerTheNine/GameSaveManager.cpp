#include "GameSaveManager.h"

#include <sys/stat.h>

#include <iostream>
#include <exception>

GameSaveManager::GameSaveManager(std::string savefile)
{
	std::cout << "GameSaveManager::GameSaveManager()" << std::endl;
	saveFile_ = savefile;
}

GameSaveManager::~GameSaveManager()
{
	std::cout << "GameSaveManager::~GameSaveManager()" << std::endl;
}

void GameSaveManager::RegisterEntity(SaveableInterface* entity)
{
	std::cout << "GameSaveManager::RegisterEntity()" << std::endl;
	saveables_.push_back(entity);
}

bool GameSaveManager::CheckSaveData()
{
	bool fileExists = false;
	struct stat s;
	if (stat(saveFile_.c_str(), &s) != -1)
	{
		fileExists = true;
	}
	return fileExists;
}

void GameSaveManager::Load()
{
	std::cout << "GameSaveManager::Load()" << std::endl;

	try
	{
		std::fstream loadSrc(saveFile_, std::fstream::in | std::fstream::binary);

		for (auto it = saveables_.begin(); it != saveables_.end(); ++it)
		{
			(*it)->Load(loadSrc);
		}

		loadSrc.close();
	}
	catch (std::exception& e)
	{
		std::cout << "ERR: " << e.what() << std::endl;
	}

}

void GameSaveManager::Save()
{
	std::cout << "GameSaveManager::Save()" << std::endl;

	try
	{
		std::fstream saveSrc(saveFile_, std::fstream::out | std::fstream::binary | std::fstream::trunc);

		for (auto it = saveables_.begin(); it != saveables_.end(); ++it)
		{
			(*it)->Save(saveSrc);
		}

		saveSrc.close();
	}
	catch (std::exception& e)
	{
		std::cout << "ERR: " << e.what() << std::endl;
	}
}