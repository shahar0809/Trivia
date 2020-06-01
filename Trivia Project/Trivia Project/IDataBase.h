#pragma once
#include <iostream>
#include <list>

struct Question
{
	std::string question;
	std::string correctAnswer;
	std::string answer2;
	std::string answer3;
	std::string answer4;
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
};


