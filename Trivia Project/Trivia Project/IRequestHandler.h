#pragma once
#include <iostream>
#include <ctime>
#include <cstddef>
#include <vector>
#include "JsonResponsePacketSerializer.h"

enum Statuses { FAILED = 0, SUCCEEDED };

struct RequestInfo
{
	int requestId;
	time_t receivalTime;
	std::vector<uint8_t> buffer;

	RequestInfo(std::string buff)
	{
		requestId = (int)(buff[0] - '0')*10+ (int)(buff[1] - '0');
		receivalTime = std::time(0);
		buffer = std::vector<uint8_t>(buff.begin() + CODE_LEN_IN_BYTES + DATA_LEN_IN_BYTES, buff.end());
	}
};

struct RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
	std::string getUsername() { return m_username; };


protected:
	std::string m_username;
};

class IRequestHandler;

struct RequestResult
{
	std::string requestBuffer;
	IRequestHandler* newHandler;
};




