#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include "io.h"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	// QUERIES
	bool doesUserExist(std::string userName);
	bool doesPasswordMatch(std::string userName, std::string password);
	bool addNewUser(std::string name, std::string password, std::string email);

	// DATABASE RELATED
	void initDatabase();
	bool openDb();
	void close();

private:
	sqlite3* db;
	void initQuestionTable();
	void insertOneQuestion(std::string question, std::string correctAnswer, std::string ans2, std::string ans3, std::string ans4);
	void createTable(std::string tableName, std::string createTableQuery);
	bool executeMsg(std::string sqlStatement, int(*callback)(void*, int, char**, char**), void* param);
	static int callbackExists(void* data, int argc, char** argv, char** azColName);
};