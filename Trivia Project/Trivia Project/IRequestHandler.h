#pragma once
#include <iostream>
#include <ctime>
#include <cstddef>
#include <vector>
#include "JsonResponsePacketSerializer.h"

struct RequestInfo
{
	std::string requestId;
	time_t time;
	Buffer buffer;
};
struct RequestResult
{
	std::string requestBuffer;
	//IRequestHandler* newHandler;
};
class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo)=0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
};




