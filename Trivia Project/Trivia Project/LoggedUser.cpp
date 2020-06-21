#include "LoggedUser.h"
LoggedUser::LoggedUser()
{}
std::string LoggedUser::getUsername()
{
	return this->m_username;
}

LoggedUser::LoggedUser(std::string userName, SOCKET socket)
{
	this->m_username = userName;
	this->m_socket = socket;
}

bool LoggedUser::operator == (LoggedUser other)
{
	return this->m_username == other.m_username;
}