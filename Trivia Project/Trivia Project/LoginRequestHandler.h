#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"

enum Statuses {FAILED = 0, SUCCEEDED};

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);

	LoginManager m_loginManager;
	RequestHandlerFactory m_handlerFactory;
};

