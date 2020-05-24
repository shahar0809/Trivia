#pragma once
#include "IDataBase.h"
#include <vector>
#include "LoggedUser.h"
#include "SqliteDatabase.h"

class  LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	LoginManager();
	bool signup(std::string userName, std::string password, std::string email);
	bool login(std::string userName, std::string password);
	bool logout(std::string userName);
};