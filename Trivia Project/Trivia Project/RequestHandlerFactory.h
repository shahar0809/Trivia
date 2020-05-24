#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "IDatabase.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManger();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};

