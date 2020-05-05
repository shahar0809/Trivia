#pragma once

#include <thread>
#include <iterator>
#include <mutex>
#include <condition_variable>
#include <string>
#include "Communicator.h"


class Server
{
private:
	Communicator m_communicator;

public:
	void run();
};
