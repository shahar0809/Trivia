#include "SqliteDatabase.h"

#define	NOT_FOUND -1

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
	if (doesFileExist == NOT_FOUND)
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
	std::string createUserTableQuery =
		"CREATE TABLE IF NOT EXISTS USERS ("
		"NAME TEXT PRIMARY KEY NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL);";

	createTable("USERS",createUserTableQuery);

	std::string createQuestionsTableQuery =
		"CREATE TABLE IF NOT EXISTS QUESTIONS ("
		"QUESTION_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
		"QUESTION TEXT NOT NULL, "
		"CORRECT_ANSWER TEXT NOT NULL, "
		"ANSWER2 TEXT NOT NULL, "
		"ANSWER3 TEXT NOT NULL, "
		"ANSWER4 TEXT NOT NULL);";

	createTable("QUESTIONS", createQuestionsTableQuery);
	initQuestionTable();
}

void SqliteDatabase::createTable(std::string tableName, std::string createTableQuery)
{
	std::string errorMsg;
	executeMsg("BEGIN;", nullptr, nullptr);

	if (!executeMsg(createTableQuery, nullptr, nullptr))
	{
		errorMsg = "Error creating the " + tableName + " table";
		executeMsg("ROLLBACK;", nullptr, nullptr);
		throw std::exception(errorMsg.c_str());
	}
	executeMsg("COMMIT;", nullptr, nullptr);
}

void SqliteDatabase::insertOneQuestion(std::string question,std::string correctAnswer,std::string ans2,std::string ans3,std::string ans4)
{
	std::string sqlMsg("INSERT INTO	QUESTIONS(QUESTION,CORRECT_ANSWER,ANSWER2,ANSWER3,ANSWER4) VALUES('"
		+ question + "','"+ correctAnswer + "','" + ans2 + "','"+ ans3+"','"+ ans4+"');");
	executeMsg((char*)sqlMsg.c_str(), nullptr, nullptr);
}

void SqliteDatabase::initQuestionTable()
{
	insertOneQuestion("Who is Eddie Vedder?", "Musician", "Computer", "Phone model", "TV Show");
	insertOneQuestion("What is the title of Labron James?", "The king", "The elevator", "The leader", "The iceman");
	insertOneQuestion("What is FLAC?", "Audio file", "Fast-Low-And-Crawl", "Movie file", "Computers Company name");
	insertOneQuestion("Nokia is...?", "Connecting people", "Make you in love", "The best you will ever hear", "Small but Smart");
	insertOneQuestion("What there is on the roof?", "Fiddler", "Cat", "Monument", "Light");
	insertOneQuestion("What is DNS?", "Domain Name System", "Data Non-Structurable", "Do Not Scratch", "audio file");
	insertOneQuestion("What NBA team does Omri Caspi plays for?", "Sacramento Kings", "Clevlend Cavs", "Atlanta Hawks", "Toronto Raptors");
	insertOneQuestion("On which instruments Adler Trio play?", "Harmonicas", "Clarinet, Trombon, Trumpet", "Guitar, Keyboard, Bass", "Violin, Viola, Chelo");
	insertOneQuestion("What is the name of the Manager of Magshimim?", "Hadas", "Michal", "Uri", "Itay");
	insertOneQuestion("Neo is a character in which movie?", "Matrix", "Lord of the Ring", "Fight Club", "Intouchables");
}

std::list<std::string> SqliteDatabase::getQuestions(int maybeNumOfQuestions)
{
	std::list<std::string> g;
	return g;
}
float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
	return 7.0;
}
int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
	return 7;
}
int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
	return 6;
}
int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	return 5;
}