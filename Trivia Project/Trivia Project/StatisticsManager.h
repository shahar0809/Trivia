#pragma once 
#include "IDataBase.h"
#include <sstream>
#include <iomanip>
#include <tuple>

struct UserStatistics
{
	float avgAnswerTime;
	int correctAnswers;
	int totalAnswers;
	int numOfGames;

	

	std::string toString()
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(3) << avgAnswerTime;

		return 
			stream.str() + ","+
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

