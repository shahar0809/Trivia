#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
	this->m_database = db;
}

std::pair<UserStatistics, std::vector<Score>> StatisticsManager::getStatistics(std::string username)
{
	UserStatistics userStats = UserStatistics
	{
		this->m_database->getPlayerAverageAnswerTime(username),
		this->m_database->getNumOfCorrectAnswers(username),
		this->m_database->getNumOfTotalAnswers(username),
		this->m_database->getNumOfPlayerGames(username)
	};

	return std::pair<UserStatistics, std::vector<Score>> { userStats, m_database->getHighScores() };
}