#pragma once
#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include <thread>
#include <iterator>
#include <mutex>
#include <condition_variable>
#include <string>
#include "Communicator.h"

#define EXIT_REQUEST "EXIT"

class Server
{
private:
	Communicator m_communicator;

public:
	void run();
};

