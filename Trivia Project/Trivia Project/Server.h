#pragma once
#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include <thread>
#include <iterator>
#include <mutex>
#include <condition_variable>
#include <string>
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

#define EXIT_REQUEST "EXIT"

class Server
{
private:
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
	IDatabase* m_database;

public:
	void run();
};

