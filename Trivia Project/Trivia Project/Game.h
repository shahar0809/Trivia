#pragma once
#include <map>
//#include "GameManager.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include <iostream>
#include <vector>
#include "Room.h"
#include "Question.h"

struct GameData
{
	Question* currentQuestion;
	unsigned int currentQuestionIndex = 0;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averangeAnswerTime;
};

class GameManager;

class Game
{
public:
	Game(IDatabase* db,Room r);

	Question getQuestionForUser(LoggedUser user);
	int submitAnswer(LoggedUser user, int answerId);
	bool removePlayer(LoggedUser user);
	bool checkUserIsInGame(LoggedUser user);

	bool operator==(const Game& other) const;
	bool operator<(const Game& other) const;
	int getId();
	std::map<LoggedUser, GameData> getPlayersGameData();

private:
	std::vector<Question>* m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_Id;
};





