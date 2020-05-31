#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{ 
	this->m_database = NULL; 
	this->m_StatisticsManager = NULL; 
}
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	this->m_database = db;
	this->m_StatisticsManager = StatisticsManager(db);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_database);
}

// LoginManager getter
LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return new MenuRequestHandler();
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}