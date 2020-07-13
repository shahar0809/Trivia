#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "LoggedUser.h"
#include <sstream>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int timeForQuestion ;
	unsigned int numOfQuestions;
	unsigned int isActive;

	std::string toString()
	{
		return std::to_string(id) + "," + name + "," +
			std::to_string(maxPlayers) + "," +
			std::to_string(timeForQuestion) + "," +
			std::to_string(numOfQuestions) + "," +
			std::to_string(isActive);
	}
};

class Room
{
public:
	Room();
	Room(int id, RoomData data,LoggedUser user);
	~Room();

	bool addUser(LoggedUser user);
	bool removeUser(LoggedUser user);
	std::vector<LoggedUser> getAllUsers();
	RoomData getMetadata();
	void setMetadata(RoomData data) { this->m_metadata = data; };

	std::vector<std::string> getAllUsernames();
	bool getHasGameBegun() { return hasGameBegun; };
	void setHasGameBegun(bool hasGameBegun) { this->hasGameBegun = hasGameBegun; };

private:
	RoomData m_metadata;
	std::vector<LoggedUser>  m_users;
	bool hasGameBegun;
};