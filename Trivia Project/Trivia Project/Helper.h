#pragma once
#include "Communicator.h"
#include <WinSock2.h>

#define DATA_LEN_IN_BYTES 4
#define CODE_LEN_IN_BYTES 1
class Helper
{
public:
	char* getPartFromSocket(SOCKET sc, int bytesNum);
	std::string getAllTheSocket(SOCKET sc);
	void sendData(SOCKET sc, std::string message);
};