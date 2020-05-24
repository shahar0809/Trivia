#include "LoginManager.h"

void LoginManager::signup(std::string userName, std::string password, std::string email)
{
	this->m_database->addNewUser(userName, password, email);
}

void LoginManager::login(std::string userName, std::string password)
{
	if (this->m_database->doesUserExist(userName) && this->m_database->doesPasswordMatch(userName, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(userName));
		return true;
	}
	std::cerr << "User doesn't exist." << std::endl;
	return false;
}

void LoginManager::logout(std::string userName)
{
	std::vector<LoggedUser>::iterator it;
	for (it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if (it->getUsername() == userName)
		{
			this->m_loggedUsers.erase(it);
		}
	}
}

LoginManager::LoginManager()
{
	this->m_database = &SqliteDatabase();
}