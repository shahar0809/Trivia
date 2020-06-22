#pragma once
<<<<<<< HEAD
=======

#include "MenuRequestHandler.h"
>>>>>>> origin/develop
#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};

