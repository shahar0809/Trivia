#pragma once
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};

