#pragma once
#include "Communicator.h"
#include <WinSock2.h>

class Helper
{
public:
	char* getPartFromSocket(SOCKET sc, int bytesNum);
	std::string getAllTheSocket(SOCKET sc);
	void sendData(SOCKET sc, std::string message);
};