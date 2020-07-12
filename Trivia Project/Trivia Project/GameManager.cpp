#include "GameManager.h"

GameManager::GameManager(IDatabase* db)
{
	this->database = db;
}

Game* GameManager::createGame(Room room)
{
	Game * game = new Game(this->database,room);
	this->m_games.push_back(*game);
	return game;
}

// This function removes the game that the given logged user attends.
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

bool GameManager::deleteGame(Game * g)
{
	std::vector<Game>::iterator it;

	for (it = this->m_games.begin(); it != this->m_games.end(); it++)
	{
		if (it->getId() == g->getId())
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
	throw std::exception();
}

std::vector<PlayerResults> GameManager::getGameResults(LoggedUser user)
{
	std::map<LoggedUser, GameData>* playersData = this->getGame(user)->getPlayersGameData();
	std::vector<PlayerResults> results;

	// Updating that the current user has finished the game
	auto player = playersData->find(user);

	if (player != playersData->end())
	{
		player->second.isFinished = true;
	}

	if (!isEveryoneFinished(user))
	{
		throw std::string("Not all the players are finished");
	}

	for (auto playerData : *playersData)
	{
		LoggedUser user = playerData.first;
		GameData gameData = playerData.second;

		PlayerResults playerDetails
		{ 
			user.getUsername(),
			gameData.correctAnswerCount,
			gameData.wrongAnswerCount,
			gameData.averangeAnswerTime 
		};
		results.push_back(playerDetails);
	}

	updateResultsInDatabase(user);
	player->second.hasGotResults = true;

	if (allGotResults(user))
	{
		deleteGame(user);
	}
	return results;
}

Question GameManager::getQuestion(LoggedUser user)
{
	return getGame(user)->getQuestionForUser(user);
}

bool GameManager::isEveryoneFinished(LoggedUser user)
{
	std::map<LoggedUser, GameData>* playersData = this->getGame(user)->getPlayersGameData();
	for (auto user : *playersData)
	{
		if (!user.second.isFinished)
			return false;
	}
	return true;
}

bool GameManager::allGotResults(LoggedUser user)
{
	std::map<LoggedUser, GameData>* playersData = this->getGame(user)->getPlayersGameData();
	for (auto user : *playersData)
	{
		if (!user.second.hasGotResults)
			return false;
	}
	return true;
}

bool GameManager::removePlayer(LoggedUser user)
{
	if (this->getGame(user))//Check user is in game.
	{
		updateResultsInDatabase(user);
		this->getGame(user)->removePlayer(user);
		return true;
	}
	return false;
}

void GameManager::updateResultsInDatabase(LoggedUser user)
{
	// Update statistics table.
	std::map<LoggedUser, GameData>* playersData = this->getGame(user)->getPlayersGameData();
	auto data = (*playersData)[user];
	this->database->insertStatistics(this->getGame(user)->getId(), user.getUsername(),
		data.correctAnswerCount, data.wrongAnswerCount,
		data.averangeAnswerTime);

	// Update scores table.
	if (data.wrongAnswerCount * WRONG_ANSWER_POINTS + data.correctAnswerCount * CORRECT_ANSWER_POINTS < 0)
	{
		this->database->insertScore(user.getUsername(), 0);
	}
	else
	{
		this->database->insertScore(user.getUsername(),
			data.wrongAnswerCount * WRONG_ANSWER_POINTS +
			data.correctAnswerCount * CORRECT_ANSWER_POINTS);
	}
}