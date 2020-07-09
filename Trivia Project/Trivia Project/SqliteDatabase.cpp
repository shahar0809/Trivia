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

int SqliteDatabase::statisticsCallback(void* data, int argc, char** argv, char** azColName)
{
	float* queryResult = static_cast<float*>(data);
	*queryResult = atof(argv[0]);
	return 0;
}

int SqliteDatabase::questionsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Question>* questionsList = (std::vector<Question>*)data;
	Question* question = new Question();

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "QUESTION")
		{
			question->setQuestion(std::string(argv[i]));
		}
			

		//There is no matter what answer it is...
		//Correct answer will be alwayes the first because of the order in the DB
		if(std::string(azColName[i]) == "ANSWER2" || 
			std::string(azColName[i]) == "ANSWER3" || 
			std::string(azColName[i]) == "ANSWER4" )
			question->addPossibleAnswer(std::string(argv[i]));
		if (std::string(azColName[i]) == "CORRECT_ANSWER")
			question->setCorrectAnswer(std::string(argv[i]));
	}

	questionsList->push_back(*question);
	return 0;
}

int SqliteDatabase::scoresCallback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<Score>* scoresList = (std::vector<Score>*)data;
	Score score;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "USERNAME")
			score.username = argv[i];

		else if (std::string(azColName[i]) == "POINTS")
			score.score = atoi(argv[i]);
	}

	scoresList->push_back(score);
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
	createUserTable();

	createQuestionsTable();
	initQuestionTable();

	createStatisticsTable();
	createScoreTable();
}

void SqliteDatabase::createUserTable()
{
	std::string createUserTableQuery =
		"CREATE TABLE IF NOT EXISTS USERS ("
		"NAME TEXT PRIMARY KEY NOT NULL, "
		"PASSWORD TEXT NOT NULL, "
		"EMAIL TEXT NOT NULL);";

	createTable("USERS", createUserTableQuery);
}

void SqliteDatabase::createQuestionsTable()
{
	std::string createQuestionsTableQuery =
		"CREATE TABLE IF NOT EXISTS QUESTIONS ("
		"QUESTION_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
		"QUESTION TEXT NOT NULL, "
		"CORRECT_ANSWER TEXT NOT NULL, "
		"ANSWER2 TEXT NOT NULL, "
		"ANSWER3 TEXT NOT NULL, "
		"ANSWER4 TEXT NOT NULL);";

	createTable("QUESTIONS", createQuestionsTableQuery);
}

void SqliteDatabase::createStatisticsTable()
{ 
	std::string createStatisticsTableQuery =
		"CREATE TABLE IF NOT EXISTS STATISTICS ("
		"GAME_ID INTEGER NOT NULL, "
		"USERNAME TEXT NOT NULL, "
		"CORRECT_ANSWERS INTEGER NOT NULL, "
		"WRONG_ANSWERS INTEGER NOT NULL,"
		"AVG_ANSWER_TIME FLOAT NOT NULL);";

	createTable("STATISTICS", createStatisticsTableQuery);
}

void SqliteDatabase::createScoreTable()
{
	std::string createScoreTableQuery =
		"CREATE TABLE IF NOT EXISTS SCORE ("
		"USERNAME TEXT PRIMARY KEY NOT NULL, "
		"POINTS INTEGER NOT NULL);";

	createTable("SCORE", createScoreTableQuery);
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
	std::string sqlMsg("INSERT INTO	QUESTIONS"
		"(QUESTION, CORRECT_ANSWER, ANSWER2, ANSWER3, ANSWER4) VALUES('" +
		question + "','" + 
		correctAnswer + "','" + 
		ans2 + "','" + 
		ans3+"','" + 
		ans4+"');");

	executeMsg(sqlMsg, nullptr, nullptr);
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

std::vector<Question>* SqliteDatabase::getQuestions(int maybeNumOfQuestions)
{
	std::vector<Question> *questionsList = new std::vector<Question>();
	executeMsg("SELECT * FROM QUESTIONS;", questionsCallback, questionsList);
	return questionsList;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
	std::string sqlQuery = "SELECT AVG(ANSWER_TIME) FROM STATISTICS "
		"WHERE USERNAME = '" + username + "';";

	float queryResult;
	executeMsg(sqlQuery, statisticsCallback, &queryResult);
	return queryResult;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
	std::string sqlQuery = "SELECT COUNT(*) FROM STATISTICS "
		"WHERE USERNAME = '" + username + "' AND "
		"IS_CORRECT = 1;";

	float queryResult;
	executeMsg(sqlQuery, statisticsCallback, &queryResult);
	return (int)(queryResult);
}

int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
	// Each record in the table represents an answer of a user.
	std::string sqlQuery = "SELECT COUNT(*) FROM STATISTICS "
		"WHERE USERNAME = '" + username + "';";
		
	float queryResult;
	executeMsg(sqlQuery, statisticsCallback, &queryResult);
	return (int)(queryResult);
}

int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	std::string sqlQuery = "SELECT COUNT(*) FROM ("
		"SELECT DISTINCT GAME_ID FROM STATISTICS "
		"WHERE USERNAME = '" + username + "');";

	float queryResult;
	executeMsg(sqlQuery, statisticsCallback, &queryResult);
	return (int)(queryResult);
}

std::vector<Score> SqliteDatabase::getHighScores()
{
	std::string sqlQuery = "SELECT * FROM SCORE ORDER BY POINTS DESC LIMIT " + std::to_string(HIGHSCORE_LIMIT) + ";";
	std::vector<Score> highScore;
	executeMsg(sqlQuery, scoresCallback, &highScore);
	return highScore;
}

void SqliteDatabase::insertScore(std::string username, int points)
{
	std::string sqlMsg;
	if (!doesUserHaveScore(username))
	{
		sqlMsg = "INSERT INTO	SCORE"
			"(USERNAME, POINTS) VALUES('" +
			username + "'," +
			std::to_string(points) + ");";
	}
	else
	{
		sqlMsg = "UPDATE SCORE SET POINTS = "+ std::to_string(points+getScore(username))+
			" WHERE USERNAME LIKE '" + username+ "';";
	}
	

	executeMsg(sqlMsg, nullptr, nullptr);
}

void SqliteDatabase::insertStatistics(int roomId, std::string username, int correctAnswers, int wrongAnswers, float avgTime)
{
	std::string sqlMsg("INSERT INTO STATISTICS ("
		"GAME_ID,USERNAME,CORRECT_ANSWERS,WRONG_ANSWERS, AVG_ANSWER_TIME) VALUES(" +
		std::to_string(roomId)+",'"+username + "'," +
		std::to_string(correctAnswers) +","+std::to_string(wrongAnswers) +","+std::to_string(avgTime)+");");

	executeMsg(sqlMsg, nullptr, nullptr);
}

bool SqliteDatabase::doesUserHaveScore(std::string userName)
{
	bool userExist = false;
	std::string sqlMsg = "SELECT * FROM SCORE WHERE USERNAME ='" + userName + "';";
	executeMsg(sqlMsg, callbackExists, &userExist);
	return userExist;
}

int SqliteDatabase::getScore(std::string username)
{
	for (auto score : getHighScores())
	{
		if (score.username == username)
		{
			return score.score;
		}
	}
}