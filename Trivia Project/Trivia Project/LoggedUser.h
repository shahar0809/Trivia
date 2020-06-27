#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
class LoggedUser
{
private:
	std::string m_username;

public:
	LoggedUser();
	LoggedUser(std::string userName);
	std::string getUsername();
	bool operator == (LoggedUser other);
};