#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	unsigned int averageAnswerTime;

	std::string toString()
	{
		return username + "'" +
			std::to_string(correctAnswersCount) + "'" +
			std::to_string(wrongAnswersCount) + "'" +
			std::to_string(averageAnswerTime) + "'";
	}
};


class Game;
class GameManager
{
public:
	Game* createGame(Room r);
	bool deleteGame(LoggedUser user);
	Game* getGame(LoggedUser);
	std::vector<PlayerResults> getGameResults(LoggedUser);
	Question getQuestion(LoggedUser user);
private:
	IDatabase* database;		
	std::vector<Game> m_games;
};

