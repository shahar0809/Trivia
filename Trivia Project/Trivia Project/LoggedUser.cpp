#include "LoggedUser.h"
LoggedUser::LoggedUser()
{}
std::string LoggedUser::getUsername()
{
	return this->m_username;
}

LoggedUser::LoggedUser(std::string userName)
{
	this->m_username = userName;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return this->m_username == other.m_username;
}