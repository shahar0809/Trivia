#include "Helper.h"

/* Receives a buffer from the client through socket, according to the bytesNum. */
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

	data[bytesNum] = NULL;
	return data;
}

/* Sends a buffer to the client through socket. */
void Helper::sendData(SOCKET sc, std::string message)
{
	std::string binStr = convertToBinary(message);
	const char* data = binStr.c_str();

	if (send(sc, data, binStr.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

/* Returns the request from the client, after being converted to ASCII. */
std::string Helper::getAllTheSocket(SOCKET sc)
{
	// Getting the code of the request
	std::string	buffer = Helper::getPartFromSocket(sc, CODE_LEN_IN_BYTES * SIZE_OF_BYTE);

	// Case code len bigger than 1
	if (buffer == "9")
	{
		buffer+= Helper::getPartFromSocket(sc, CODE_LEN_IN_BYTES * SIZE_OF_BYTE); // Getting second digit of code
	}

	// Getting the data length
	std::string dataLength = Helper::getPartFromSocket(sc, DATA_LEN_IN_BYTES * SIZE_OF_BYTE);
	buffer += dataLength;
	dataLength = convertToAscii(dataLength);

	// Getting the data from the packet
	buffer += Helper::getPartFromSocket(sc, SIZE_OF_BYTE * std::stoi(dataLength));
	std::cout << convertToAscii(buffer) << std::endl;
	//convertToAscii(buffer);
	return convertToAscii(buffer);
}

/* Converts a buffer from ASCII to binary. */
std::string Helper::convertToBinary(std::string str)
{
	std::string binString;
	for (auto element : str)
	{
		binString += (std::bitset<8>(element)).to_string();
	}
	return binString;
}

/* Converts a buffer from binary to ASCII. */
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
