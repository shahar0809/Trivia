#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include <string>
#include <mutex>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#define HELLO_MSG "Hello"
#define MSG_LEN 5
#define PORT 1050

class Communicator
{
public:
	void startHandleRequests();
	void setIsEnded(bool isEnded);

private:
	void bindAndListen();
	void handleNewClient(std::pair<SOCKET, IRequestHandler*> client);

	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_listeningSocket;
	bool m_isEnded;
};

