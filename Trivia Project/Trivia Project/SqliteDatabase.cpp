#include "SqliteDatabase.h"

/**
* Checks if a user exists by its username.
* @param userName: the username we search for in the database.
* return: exists / doesn't exist (true / false)
*/
bool SqliteDatabase::doesUserExist(std::string userName)
{
	bool userExist = false;
	std::string sqlMsg = "SELECT * FROM USERS WHERE NAME ='" + userName + "';";
	executeMsg(sqlMsg, callbackExists, &userExist);
	return userExist;
}

/**
* Checks if the inputted password matches the user's password.
* @param userName: the user's name.
* return: matches / doesn't match (true / false)
*/
bool SqliteDatabase::doesPasswordMatch(std::string userName,std::string password)
{
	bool passwordMatch = false;
	std::string sqlMsg = "SELECT *" 
		"FROM USERS WHERE NAME ='" + userName + 
		"' AND PASSWORD = '" + password + "';";

	executeMsg(sqlMsg, callbackExists, &passwordMatch);
	return passwordMatch;
}

/**
* This function is called when the SELECT query gets data. Returns in @param data if a user exists or not.
*/
int SqliteDatabase::callbackExists(void* data, int argc, char** argv, char** azColName)
{
	bool* doesExist = static_cast<bool*>(data);
	*doesExist = true;
	return 0;
}

/**
* Adds a new user to the database.
* @param name: the username.
* @param password: the user's password.
* @param email: the user's email.
* return: None.
*/
bool SqliteDatabase::addNewUser(std::string name, std::string password, std::string email)
{
	if (doesUserExist(name))
	{
		return false;
	}

	std::string sqlQuery = "INSERT INTO USERS"
		"(NAME,PASSWORD,EMAIL)"
		" VALUES("
		"'" + name + "', "
		"'" + password + "', "
		"'" + email + "');";

	executeMsg(sqlQuery.c_str(), nullptr, nullptr);
	return true;
}

/**
* Opens the database.
* return: opened successfully / failed to open (true / false)
*/
bool SqliteDatabase::openDb()
{
	std::string dbFileName = "triviaDB.sqlite";

	int doesFileExist = _access(dbFileName.c_str(), 0);
	int result = sqlite3_open(dbFileName.c_str(), &db);
	if (result != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	if (doesFileExist == -1)
	{
		initDatabase();
	}
	return true;
}

/**
* Executes a SQL query on the opened databse.
* @param sqlStatement: the SQL query
* @param callback: the callback function to the query (if there's one)
* @param param: query result
*/
bool SqliteDatabase::executeMsg(std::string sqlStatement, int(*callback)(void*, int, char**, char**), void* param)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), callback, param, &errMessage);

	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return false;
	}
	
	return true;
}

/*
Constructor
*/
SqliteDatabase::SqliteDatabase()
{
	this->openDb();
}

/**
* Closes the opened database.
* return: None.
*/
void SqliteDatabase::close()
{
	sqlite3_close(db);
	db = nullptr;
}

/*
Destructor
*/
SqliteDatabase::~SqliteDatabase()
{
	close();
}

/**
* Initializes the database by creating all the necessary tables (USERS, ALBUMS, PICTURES, TAGS).
* Input: None
* Ouput: None
*/
void SqliteDatabase::initDatabase()
{
	executeMsg("BEGIN;", nullptr, nullptr);

	std::string createTableQuery =
		"CREATE TABLE IF NOT EXISTS USERS ("
		"NAME TEXT PRIMARY KEY NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL);";

	if (!executeMsg(createTableQuery, nullptr, nullptr))
	{
		executeMsg("ROLLBACK;", nullptr, nullptr);
		throw std::exception("Error creating the USERS table");
	}
	executeMsg("COMMIT;", nullptr, nullptr);
}