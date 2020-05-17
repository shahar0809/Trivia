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
};

struct RequestResult
{
	Buffer requestBuffer;
	//IRequestHandler* newHandler;
};

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
};




