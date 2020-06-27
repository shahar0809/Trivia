#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
	this->m_database = db;
}

std::pair<UserStatistics, std::vector<Score>> StatisticsManager::getStatistics(std::string username)
{
	int numOfGames = this->m_database->getNumOfPlayerGames(username);
	UserStatistics userStats;
	if(numOfGames == 0)
	{ 
		userStats = UserStatistics
		{
			0,0,0,numOfGames
		};
	}
	else
	{
		userStats = UserStatistics
		{
			this->m_database->getPlayerAverageAnswerTime(username),
			this->m_database->getNumOfCorrectAnswers(username),
			this->m_database->getNumOfTotalAnswers(username),
			numOfGames
		};
	}

	return std::pair<UserStatistics, std::vector<Score>> { userStats, m_database->getHighScores() };
}

