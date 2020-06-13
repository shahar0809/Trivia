#pragma once 
#include "IDataBase.h"
#include <tuple>
struct UserStatistics
{
	float avgAnswerTime;
	int correctAnswers;
	int totalAnswers;
	int numOfGames;

	std::string toString()
	{
		return 
			std::to_string(avgAnswerTime) + ","+
			std::to_string(correctAnswers) + "," +
			std::to_string(totalAnswers) + "," +
			std::to_string(numOfGames);
	}
};

class StatisticsManager
{
public:
	StatisticsManager() { this->m_database = NULL; };
	StatisticsManager(IDatabase* db);
	std::pair<UserStatistics, std::vector<Score>> getStatistics(std::string username);

private:
	IDatabase* m_database;
};

