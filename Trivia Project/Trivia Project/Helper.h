#pragma once
#include "Communicator.h"
#include <WinSock2.h>

#define DATA_LEN_IN_BYTES 4
#define CODE_LEN_IN_BYTES 1
class Helper
{
public:
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static std::string getAllTheSocket(SOCKET sc);
	static void sendData(SOCKET sc, std::string message);
	static std::string convertToBinary(std::string str);
	static std::string convertToAscii(std::string str);
};