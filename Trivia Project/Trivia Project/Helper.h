#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <WinSock2.h>

#define NO_FLAGS 0
#define SIZE_OF_BYTE 8

enum ByteSizes{ CODE_LEN_IN_BYTES = 1, DATA_LEN_IN_BYTES = 4};

class Helper
{
public:
	// Socket related
	static char* getPartFromSocket(SOCKET sc, int bytesNum);
	static std::string getAllTheSocket(SOCKET sc);
	static void sendData(SOCKET sc, std::string message);

	// Conversion to and from binary related
	static std::string convertToBinary(std::string str);
	static std::string convertToAscii(std::string str);
};