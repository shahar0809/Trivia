#include "GameManager.h"


Game* GameManager::createGame(Room room)
{
	Game * game = new Game(room.getAllUsers(),room.getMetadata().id);
	this->m_games.push_back(*game);
	return game;
}

//This function removes the game that the given logged user attends.
bool GameManager::deleteGame(LoggedUser user)
{
	std::vector<Game>::iterator it;
	for (it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (it->checkUserIsInGame(user))
		{
			this->m_games.erase(it);
			return true;
		}
	}
	return false;
}

Game* GameManager::getGame(LoggedUser user)
{
	std::vector<Game>::iterator it;
	for (it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (it->checkUserIsInGame(user))
		{
			return &(*it);
		}
	}
	return nullptr;
}