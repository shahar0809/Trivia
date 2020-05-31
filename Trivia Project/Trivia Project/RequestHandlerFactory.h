#pragma once
#include "LoginManager.h"
//#include "MenuRequestHandler.h"
#include "IDatabase.h"
#include "RoomManager.h"

struct StatisticsManager
{
public:
	void getStatistics() {  };
private:
	IDatabase*  m_database;
};

class MenuRequestHandler;
class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory() { this->m_database = NULL; };
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManger();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};

