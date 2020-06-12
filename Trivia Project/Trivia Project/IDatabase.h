#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

#define HIGHSCORE_LIMIT 5

struct Question
{
	std::string question;
	std::string correctAnswer;
	std::string answer2;
	std::string answer3;
	std::string answer4;
};

struct Score
{
	std::string username;
	unsigned int score;

	std::string toString()
	{
		return
			username +
			"-"+
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

	virtual std::list<Question> getQuestions(int maybeNumOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual std::vector<Score> getHighScores() = 0;

private:
	virtual void initDatabase() = 0;
};


