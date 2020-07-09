#include "GameManager.h"
#define CORRECT_ANSWER_POINTS 2
#define WRONG_ANSWER_POINTS -1

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

std::vector<PlayerResults> GameManager::getGameResults(LoggedUser user)
{
	std::map<LoggedUser, GameData> playersData = this->getGame(user)->getPlayersGameData();
	std::vector<PlayerResults> results;

	// Updating that the current user has finished the game
	auto player = playersData.find(user);
	player->second.isFinished = true;

	if (!isEveryoneFinished(user))
	{
		return results;
	}

	for (auto playerData : playersData)
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
	return results;
}
Question GameManager::getQuestion(LoggedUser user)
{
	return getGame(user)->getQuestionForUser(user);
}

bool GameManager::isEveryoneFinished(LoggedUser user)
{
	std::map<LoggedUser, GameData> playersData = this->getGame(user)->getPlayersGameData();
	for (auto user : playersData)
	{
		if (!user.second.isFinished)
			return false;
	}
	return true;
}

bool GameManager::removePlayer(LoggedUser user)
{
	if (this->getGame(user)->removePlayer(user))
	{
		updateResultsInDatabase(user);
		return true;
	}
	return false;
}

void GameManager::updateResultsInDatabase(LoggedUser user)
{
	//Update statistics table.
	std::map<LoggedUser, GameData> playersData = this->getGame(user)->getPlayersGameData();
	this->database->insertStatistics(this->getGame(user)->getId(), user.getUsername(),
		playersData[user].correctAnswerCount, playersData[user].wrongAnswerCount,
		playersData[user].averangeAnswerTime);

	//Update socre table.
	this->database->insertScore(user.getUsername(),
		playersData[user].wrongAnswerCount * WRONG_ANSWER_POINTS +
		playersData[user].correctAnswerCount * CORRECT_ANSWER_POINTS);
}