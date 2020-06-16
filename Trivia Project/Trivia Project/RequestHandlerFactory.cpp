#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{ 
	this->m_database = NULL; 
	this->m_StatisticsManager = NULL; 
	//this->m_roomManager;
}
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	this->m_database = db;
	this->m_StatisticsManager = StatisticsManager(db);
	this->m_roomManager = new RoomManager();
	this->m_loginManager = *new LoginManager(db);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}

// LoginManager getter
LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(std::string username)
{
	return new MenuRequestHandler(username, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
RoomManager* RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler()
{
	return new RoomMemberRequestHandler();
}
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler()
{
	return new RoomAdminRequestHandler();
}