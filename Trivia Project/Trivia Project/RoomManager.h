#pragma once
#include <map>
#include "Room.h"
#include <sstream>

#define NOT_EXIST -1

class RoomManager
{
public:
	RoomManager() { roomId = 0; };

	// Managing rooms
	void createRoom(LoggedUser user, RoomData data);
	bool deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();

private:
	std::map<int,Room> m_rooms;
	int roomId;  // Holds the id of the last room created.
};