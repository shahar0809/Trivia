#pragma once
#include <map>
//#include "GameManager.h"
#include "IDatabase.h"
#include "LoggedUser.h"


struct GameData
{
	Question currentQuestion;
	unsigned int currentQuestionIndex = 0;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averangeAnswerTime;
};


class GameManager;
class Game
{
public:
	Game(std::vector<LoggedUser> users, int id);
	Question getQuestionForUser(LoggedUser user);
	bool submitAnswer();
	bool removePlayer(LoggedUser user);
	bool checkUserIsInGame(LoggedUser user);
	bool operator == (Game other);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int id;
};





