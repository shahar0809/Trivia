#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include "io.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string userName, std::string password);
	void addNewUser(std::string name, std::string password, std::string email);
	bool openDb();
	void close();
private:
	sqlite3* db;
	bool executeMsg(char* sqlStatement, int(*callback)(void*, int, char**, char**), void* param);
	static int callbackExists(void* data, int argc, char** argv, char** azColName);
};