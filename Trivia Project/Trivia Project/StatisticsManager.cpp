#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
	this->m_database = db;
}

UserStatistics StatisticsManager::getStatistics(std::string username)
{
	return UserStatistics
	{
		this->m_database->getPlayerAverageAnswerTime(username),
		this->m_database->getNumOfCorrectAnswers(username),
		this->m_database->getNumOfTotalAnswers(username),
		this->m_database->getNumOfPlayerGames(username)
	};
}