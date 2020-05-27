#include "LoggedUser.h"

std::string LoggedUser::getUsername()
{
	return this->m_username;
}
LoggedUser::LoggedUser(std::string userName)
{
	this->m_username = userName;
}