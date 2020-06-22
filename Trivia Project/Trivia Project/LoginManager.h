#pragma once
#include "IDataBase.h"
#include <vector>
#include "LoggedUser.h"
#include "SqliteDatabase.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	LoginManager() { m_database = NULL; };
	LoginManager(IDatabase* db) { m_database = db; };

	bool signup(std::string userName, std::string password, std::string email);
	LoggedUser* login(std::string userName, std::string password, SOCKET socket);
	bool logout(std::string userName);
};