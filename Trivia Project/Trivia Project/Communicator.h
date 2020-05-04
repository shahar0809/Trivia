#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include "IRequestHandler.h"

class Communicator
{
public:
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient();

	std::map<SOCKET, IRequestHandler*> m_clients;
};

