#pragma once
#include <iostream>
#include <ctime>
#include <cstddef>
#include <vector>
#include "JsonResponsePacketSerializer.h"

struct RequestInfo
{
	int requestId;
	time_t receivalTime;
	std::vector<uint8_t> buffer;

	RequestInfo(std::string buff)
	{
		std::vector<uint8_t> packet(buff.begin(), buff.end());
		requestId = (int)packet[0];
		receivalTime = std::time(0);
		buffer = std::vector<uint8_t>(packet.begin() + 5, packet.end());
	}
};

struct RequestResult
{
	std::string requestBuffer;
	//IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
};




