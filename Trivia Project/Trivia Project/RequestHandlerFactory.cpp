#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory()
{ 
	this->m_database = NULL; 
	this->m_StatisticsManager = NULL; 
}
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	this->m_database = db;
	this->m_StatisticsManager = StatisticsManager(db);
	this->m_roomManager = new RoomManager();
	this->m_loginManager = new LoginManager(db);
	this->m_gameManager = new GameManager(db);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(this);
}

// LoginManager getter
LoginManager* RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser* user)
{
	return new MenuRequestHandler(user, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}
RoomManager* RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger)
{
	return new RoomMemberRequestHandler(room, user, handlerFactory, roomManger);
}
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger)
{
	return new RoomAdminRequestHandler(room, user, handlerFactory, roomManger);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory)
{
	return new GameRequestHandler(user, handlerFactory);
}

GameManager* RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}