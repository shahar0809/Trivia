#include "RoomManager.h"


Room* RoomManager::createRoom(LoggedUser user, RoomData data)
{
	m_rooms[roomId] = *new Room(this->roomId, data, user);
	this->roomId++;
	return &(m_rooms[roomId - 1]);
}

bool RoomManager::deleteRoom(int ID)
{
	std::map<int, Room>::iterator it;
	it = this->m_rooms.find(ID);
	if (it != this->m_rooms.end())
	{
		RoomData data = it->second.getMetadata();
		data.isActive = false;
		it->second.setMetadata(data);
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

	for (auto room : m_rooms)
	{
		RoomData data = room.second.getMetadata();
		if (data.isActive)
			rooms.push_back(data);
	}

	return rooms;
}

Room* RoomManager::getRoom(int roomId)
{
	return &this->m_rooms[roomId];
}

int RoomManager::getLastId()
{
	return this->roomId-1;
}
