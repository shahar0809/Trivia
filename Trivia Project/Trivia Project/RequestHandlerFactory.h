#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"


class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class LoginRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser* user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger);
	GameRequestHandler* createGameRequestHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory);

	LoginManager& getLoginManger();
	StatisticsManager& getStatisticsManager();
	RoomManager* getRoomManager();
	GameManager* getGameManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	GameManager* m_gameManager;
	StatisticsManager m_StatisticsManager;
};

