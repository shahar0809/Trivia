#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "LoginRequestHandler.h"

class Communicator
{
public:
	void startHandleRequests();

private:
	SOCKET bindAndListen();
	void handleNewClient();

	std::map<SOCKET, IRequestHandler*> m_clients;
};

