#pragma once
#include <map>
#include "Room.h"
#include <sstream>

#define NOT_EXIST -1

class RoomManager
{
public:
	void createRoom(LoggedUser user);
	bool deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
private:
	std::map<int,Room> m_rooms;
	int roomId;
};