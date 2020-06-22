#include "Room.h"
#include <algorithm>

Room::Room()
{
}

Room::Room(int id, std::string name, LoggedUser user)
{
	this->m_metadata.id = id;
	this->m_metadata.name = name;
	this->m_metadata.isActive = true;
	//this->m_users.push_back(user);
}

Room::~Room()
{
	//this->m_users.clear();
}

bool Room::addUser(LoggedUser user)
{
	if (this->m_metadata.isActive && this->m_users.size() < this->m_metadata.maxPlayers)
	{
		this->m_users.push_back(user);
		return true;
	}
	return false;
}

bool Room::removeUser(LoggedUser user)
{
	std::vector<LoggedUser>::iterator it = std::find(this->m_users.begin(), this->m_users.end(), user);
	if (it != this->m_users.end())
	{
		this->m_users.erase(it);
		return true;
	}
	return false;
}

std::vector<LoggedUser> Room::getAllUsers()
{
	return this->m_users;
}

RoomData Room::getMetadata()
{
	return this->m_metadata;
}