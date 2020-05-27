#pragma once
#include "IDatabase.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

enum Statuses {FAILED = 0, SUCCEEDED};


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() {};
	LoginRequestHandler(IDatabase* db);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);

	LoginManager m_loginManager;
	RequestHandlerFactory m_handlerFactory;
};
