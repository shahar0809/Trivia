#include "Game.h"
#include "GameManager.h"

Game::Game(IDatabase* db,Room r)
{
	this->m_Id = r.getMetadata().id;
	//this->m_questions = new std::vector<Question>(r.getMetadata().numOfQuestions);
	this->m_questions = db->getQuestions(r.getMetadata().numOfQuestions);
	
	GameData beginGameData{ &this->m_questions->front() , 0, 0, 0, 0 };
	
	// Initializing game data of all users
	for (auto user : r.getAllUsers())
	{
		this->m_players.insert(std::pair <LoggedUser, GameData>(user, beginGameData));
	}
}

Question Game::getQuestionForUser(LoggedUser user)
{
	int currentQuestion = m_players[user].currentQuestionIndex;
	std::vector<Question>::iterator it = this->m_questions->begin();
	m_players[user].currentQuestionIndex++;

	for (int i = 0; i < currentQuestion; i++)
	{
		if (it == this->m_questions->end())//Case there aren't enough questions, should start again?
		{
			it = this->m_questions->begin();
		}
		it++;
	}
	m_players[user].currentQuestion = &(*it);
	return *it;
}

int Game::submitAnswer(LoggedUser user, int answerId, double time)
{
	GameData* data = nullptr;
	unsigned int correctAnswerId = 0;

	try
	{
		auto it = (m_players.find(user));
		std::cout << "Is a? : " <<  it->first.operator==(LoggedUser("a")) << std::endl;

		if (it == m_players.end())
		{
			std::cout << "got end of map" << std::endl;
			return ERROR;
		}
		
		std::cout << "trying to print something: " << std::endl;
		data = &(it->second);
		std::cout << data->currentQuestion << std::endl;
		if (data->averangeAnswerTime == 0)
		{
			data->averangeAnswerTime = time;
		}
		else
		{
			data->averangeAnswerTime = (data->averangeAnswerTime + time) / 2;
		}
		std::cout << "Updated avg\n";
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

std::map<LoggedUser, GameData>* Game::getPlayersGameData()
{
	return &(this->m_players);
}

std::map<LoggedUser, GameData> Game::getPlayers()
{
	return this->m_players;
}