#include "LoginManager.h"

bool LoginManager::signup(std::string userName, std::string password, std::string email)
{
	try
	{ 
		this->m_database->addNewUser(userName, password, email);
		return true;
	}
	catch (std::exception e)
	{
		return false;
	}
}

bool LoginManager::login(std::string userName, std::string password)
{
	if (this->m_database->doesUserExist(userName) && this->m_database->doesPasswordMatch(userName, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(userName));
		return true;
	}
	std::cerr << "User doesn't exist." << std::endl;
	return false;
}

bool LoginManager::logout(std::string userName)
{
	std::vector<LoggedUser>::iterator it;
	for (it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == userName)
		{
			this->m_loggedUsers.erase(it);
			return true;
		}
	}
	return false;
}