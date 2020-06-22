#include "Helper.h"
#define NO_FLAGS 0

// recieve data from socket according byteSize
char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char *data = new char[bytesNum + 1];

	int res = recv(sc, data, bytesNum, NO_FLAGS);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// send data to socket
void Helper::sendData(SOCKET sc, std::string message)
{
	std::string binStr = convertToBinary(message);
	const char* data = binStr.c_str();

	if (send(sc, data, binStr.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Helper::getAllTheSocket(SOCKET sc)
{
	std::string	buffer = Helper::getPartFromSocket(sc, (DATA_LEN_IN_BYTES + CODE_LEN_IN_BYTES) * 8);
	buffer += Helper::getPartFromSocket(sc, 8 * std::stoi(buffer.substr(CODE_LEN_IN_BYTES, DATA_LEN_IN_BYTES)));
	return convertToAscii(buffer);
}

std::string Helper::convertToBinary(std::string str)
{
	std::string binString;
	for (auto element : str)
	{
		binString += (std::bitset<8>(element)).to_string();
	}
	return binString;
}

std::string Helper::convertToAscii(std::string str)
{
	std::string textualStr;
	std::stringstream sstream(str);

	while (sstream.good())
	{
		std::bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		textualStr += c;
	}
	return textualStr;
}
