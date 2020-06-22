#pragma once
#include "MenuRequestHandler.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory* handler);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info, SOCKET socket);

private:
	RequestResult login(RequestInfo info, SOCKET socket);
	RequestResult signup(RequestInfo info);

	LoginManager m_loginManager;
	RequestHandlerFactory m_handlerFactory;
	SOCKET m_socket;
};
