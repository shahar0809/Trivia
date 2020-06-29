#include "Game.h"
#include "GameManager.h"

Game::Game(std::vector<LoggedUser> users, int id)
{
	this->m_Id = id;
	GameData beginGameData{ nullptr, 0, 0, 0, 0 };

	// Initializing game data of all users
	for (auto user : users)
	{
		this->m_players.insert(std::pair <LoggedUser, GameData>(user, beginGameData));
	}

	/*
	std::vector<LoggedUser>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		this->m_players.insert(std::pair <LoggedUser, GameData>(*it, beginGameData));
	}*/
}


Question Game::getQuestionForUser(LoggedUser user)
{
	int currentQuestion = m_players[user].currentQuestionIndex;
	std::vector<Question>::iterator it = this->m_questions.begin();
	m_players[user].currentQuestionIndex++;

	for (int i = 0; i < currentQuestion; i++)
	{
		if (it == this->m_questions.end())//Case there aren't enough questions, should start again?
		{
			it = this->m_questions.begin();
		}
	}
	return *it;
}

int Game::submitAnswer(LoggedUser user,int answerId)
{
	std::map<LoggedUser, GameData>::iterator it;
	GameData* data = nullptr;
	unsigned int correctAnswerId = 0;

	try
	{
		data = &(m_players.find(user)->second);
		correctAnswerId = data->currentQuestion->getCorrectAnswerId();
	}
	catch (const std::exception & e)
	{
		return ERROR;
	}

	if (correctAnswerId == answerId)
	{
		data->correctAnswerCount++;
		return correctAnswerId;
	}
	else
	{
		data->wrongAnswerCount++;
		return correctAnswerId;
	}
}

bool Game::removePlayer(LoggedUser user)
{
	try
	{
		this->m_players.erase(user);
	}
	catch (const std::exception & e)
	{
		return false;
	}
	return true;
}

bool Game::checkUserIsInGame(LoggedUser user)
{
	return this->m_players.find(user) != this->m_players.end();
}

bool Game::operator==(const Game& other) const
{
	return this->m_Id == other.m_Id;
}

bool Game::operator<(const Game& other) const
{
	return this->m_Id < other.m_Id;
}

int Game::getId()
{
	return this->m_Id;
}

std::map<LoggedUser, GameData> Game::getPlayersGameData()
{
	return this->m_players;
}