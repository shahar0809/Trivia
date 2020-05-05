#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "LoginRequestHandler.h"
#include <string>
#include <mutex>

class Communicator
{
public:
	void startHandleRequests();
	void setIsEnded(bool isEnded);
private:
	SOCKET bindAndListen();
	void handleNewClient(SOCKET s);

	std::map<SOCKET, IRequestHandler*> m_clients;
	bool _isEnded;
};

