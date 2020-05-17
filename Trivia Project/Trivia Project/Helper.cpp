#include "Helper.h"
#define NO_FLAGS 0

// recieve data from socket according byteSize
std::string Helper::getPartFromSocket(SOCKET sc, int bytesNum)
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
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Helper::getAllTheSocket(SOCKET sc)
{
	std::string	buffer = this->getPartFromSocket(sc, 5);
	buffer += this->getPartFromSocket(sc, std::stoi(buffer.substr(1, 4)));
	return buffer
}