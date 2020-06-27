#include "Game.h"
#include "GameManager.h"

Game::Game(std::vector<LoggedUser> users, int id)
{
	this->id = id;
	GameData beginGameData{ 0,0,0,0,0 };
	std::vector<LoggedUser>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		this->m_players.insert(std::pair <LoggedUser, GameData>(*it, beginGameData));
	}
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
bool Game::submitAnswer()
{
	//Don't know what to do here.
	return true;
}
bool Game::removePlayer(LoggedUser user)
{
	this->m_players.erase(user);
}

bool Game::checkUserIsInGame(LoggedUser user)
{
	return this->m_players.find(user) != this->m_players.end();
}

bool Game::operator == (Game other)
{
	return id == other.id;
}

int Game::getId()
{
	return this->id;
}

std::map<LoggedUser, GameData> Game::getPlayersGameData()
{
	return this->m_players;
}