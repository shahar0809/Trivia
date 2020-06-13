#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	m_rooms[roomId] = *new Room(this->roomId, data, user);
	this->roomId++;
}

bool RoomManager::deleteRoom(int ID)
{
	std::map<int, Room>::iterator it;
	it = this->m_rooms.find(ID);

	if (it != this->m_rooms.end())
	{
		this->m_rooms.erase(it);
		return true;
	}
	return false;
}

unsigned int RoomManager::getRoomState(int ID)
{
	std::map<int, Room>::iterator it;
	it = this->m_rooms.find(ID);

	if (it != this->m_rooms.end())
		return it->second.getMetadata().isActive;

	return NOT_EXIST;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	std::map<int,Room>::iterator it;

	for (it = this->m_rooms.begin(); it != this->m_rooms.end(); it++)
	{
		rooms.push_back(it->second.getMetadata());
	}
	return rooms;
}

Room RoomManager::getRoom(int roomId)
{
	return this->m_rooms[roomId];
}