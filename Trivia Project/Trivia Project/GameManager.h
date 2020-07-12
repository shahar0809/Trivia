#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"

#define CORRECT_ANSWER_POINTS 2
#define WRONG_ANSWER_POINTS -1

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	unsigned int averageAnswerTime;

	std::string toString()
	{
		return username + "," +
			std::to_string(correctAnswersCount) + "," +
			std::to_string(wrongAnswersCount) + "," +
			std::to_string(averageAnswerTime);
	}
};

class Game;

class GameManager
{
public:
	GameManager(IDatabase* db);
	
	// General
	Game* createGame(Room r);
	bool deleteGame(LoggedUser user);
	bool deleteGame(Game* g);
	
	Question getQuestion(LoggedUser user);
	bool isEveryoneFinished(LoggedUser user);
	bool allGotResults(LoggedUser user);

	// Setters & Getters
	Game* getGame(LoggedUser);
	std::vector<PlayerResults> getGameResults(LoggedUser);

	bool removePlayer(LoggedUser user);
	void updateResultsInDatabase(LoggedUser user);

private:
	IDatabase* database;		
	std::vector<Game> m_games;
};

