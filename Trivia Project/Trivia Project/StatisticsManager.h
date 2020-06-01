#pragma once 
#include "IDataBase.h"

struct UserStatistics
{
	float avgAnswerTime;
	int correctAnswers;
	int totalAnswers;
	int numOfGames;
};

class StatisticsManager
{
public:
	StatisticsManager() { this->m_database = NULL; };
	StatisticsManager(IDatabase* db);
	UserStatistics getStatistics(std::string username);

private:
	IDatabase* m_database;
};

