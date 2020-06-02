#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers = 5;
	unsigned int timePerQuestion = 1;
	unsigned int isActive;
};

class Room
{
public:
	Room();
	Room(int id, std::string name,LoggedUser user);
	~Room();

	bool addUser(LoggedUser user);
	bool removeUser(LoggedUser user);
	std::vector<LoggedUser> getAllUsers();
	RoomData getMetadata();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};