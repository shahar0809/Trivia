#include "Room.h"
#include <algorithm>

Room::Room()
{
}

Room::Room(int id, RoomData data, LoggedUser user)
{
	this->m_metadata = data;
	this->m_metadata.id = id;
	this->m_metadata.isActive = false;
	this->m_users.push_back(user);
	this->hasGameBegun = false;
}

Room::~Room()
{
	this->m_users.clear();
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

std::vector<std::string> Room::getAllUsernames()
{
	std::vector<std::string> vec;

	for (auto user : m_users)
	{
		vec.push_back(user.getUsername());
	}
	return vec;
}