#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "IDatabase.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequesHandler();
	LoginManager& getLoginManger();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};

