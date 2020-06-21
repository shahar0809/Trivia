#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
class LoggedUser
{
private:
	std::string m_username;
	SOCKET m_socket;

public:
	LoggedUser();
	LoggedUser(std::string userName, SOCKET socket);
	std::string getUsername();
	bool operator == (LoggedUser other);
};