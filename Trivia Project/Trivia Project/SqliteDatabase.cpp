#include "SqliteDatabase.h"

bool SqliteDatabase::doesUserExist(std::string userName)
{
	bool userExist = false;
	std::string sqlMsg = "SELECT * FROM USERS WHERE NAME ='" + userName + "';";
	executeMsg((char*)sqlMsg.c_str(), callbackExists, &userExist);
	return userExist;
}

bool SqliteDatabase::doesPasswordMatch(std::string userName,std::string password)
{
	bool passwordMatch = false;
	std::string sqlMsg = "SELECT * FROM USERS WHERE NAME ='" + userName + "' AND PASSWORD = '"
		+ password + "';";
	executeMsg((char*)sqlMsg.c_str(), callbackExists, &passwordMatch);
	return passwordMatch;
}

//This function is called when the select query gets data - proves that there is such user.
int SqliteDatabase::callbackExists(void* data, int argc, char** argv, char** azColName)
{
	bool* isExist = static_cast<bool*>(data);
	*isExist = true;
	return 0;
}

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string email)
{
	std::string sqlMsg("INSERT INTO USERS(NAME,PASSWORD,EMAIL) VALUES('" + name +"','"+ password+"','"+ email+ "');");
	executeMsg((char*)sqlMsg.c_str(), nullptr, nullptr);
}

bool SqliteDatabase::openDb()
{
	std::string dbFileName = "triviaDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK) 
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	return true;
}
bool SqliteDatabase::executeMsg(char* sqlStatement, int(*callback)(void*, int, char**, char**), void* param)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callback, param, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return false;
	}
	return true;
}

SqliteDatabase::SqliteDatabase()
{
	this->openDb();
}

void SqliteDatabase::close()
{
	sqlite3_close(db);
	db = nullptr;
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}