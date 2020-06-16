#pragma once
#include "LoginManager.h"
#include "IDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"


class MenuRequestHandler;
class LoginRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(std::string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler();
	RoomAdminRequestHandler* createRoomAdminRequestHandler();
	LoginManager& getLoginManger();
	StatisticsManager& getStatisticsManager();
	RoomManager* getRoomManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager m_StatisticsManager;
};

