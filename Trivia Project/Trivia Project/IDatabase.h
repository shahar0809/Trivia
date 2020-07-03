#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include "Question.h"

#define HIGHSCORE_LIMIT 5

struct Score
{
	std::string username;
	unsigned int score;

	std::string toString()
	{
		return
			username +
			","+
			std::to_string(score);
	}
};

class IDatabase
{
public:
	virtual bool doesUserExist(std::string userName) = 0;
	virtual bool doesPasswordMatch(std::string userName, std::string password) = 0;
	virtual bool addNewUser(std::string name, std::string password, std::string email) = 0;
	virtual bool openDb() = 0;

	virtual std::vector<Question>* getQuestions(int maybeNumOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual std::vector<Score> getHighScores() = 0;

private:
	virtual void initDatabase() = 0;
};


