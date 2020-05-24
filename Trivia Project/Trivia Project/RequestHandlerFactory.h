#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
class LoginRequestHandler;
class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
public:
	LoginRequestHandler createLoginRequestHandler();
	LoginManager& getLoginManager();
};