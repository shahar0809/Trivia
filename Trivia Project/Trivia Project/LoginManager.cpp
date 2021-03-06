#include "LoginManager.h"

bool LoginManager::signup(std::string userName, std::string password, std::string email)
{
	return this->m_database->addNewUser(userName, password, email);
}

LoggedUser* LoginManager::login(std::string userName, std::string password)
{
	// Checking if the user is already connected to the server
	for (auto loggedUser : m_loggedUsers)
	{
		if (loggedUser.getUsername() == userName)
		{
			return nullptr;
		}
	}

	// If not, the log in credintals need to be checked
	if (this->m_database->doesUserExist(userName) && this->m_database->doesPasswordMatch(userName, password))
	{
		LoggedUser* user = new LoggedUser(userName);
		this->m_loggedUsers.push_back(*user);

		return user;
	}
	std::cerr << "User doesn't exist." << std::endl;
	return nullptr;
}

bool LoginManager::logout(std::string userName)
{
	std::vector<LoggedUser>::iterator it;

	/* Searching for the user in the logged users list, and if it's there, deleting it. */
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