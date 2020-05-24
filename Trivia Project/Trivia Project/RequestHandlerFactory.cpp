#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{
	this->m_database = &SqliteDatabase();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->m_database;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

// LoginManager getter
LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler menuReq = MenuRequestHandler();
	return new MenuRequestHandler();
}
