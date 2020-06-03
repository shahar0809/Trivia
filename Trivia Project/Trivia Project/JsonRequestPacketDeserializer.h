#pragma once
#include <iostream>
#include <iomanip>
#include "IRequestHandler.h"

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

/* Easy access to the json fields. */
static const char* fields[] = { 
	"username", "password", "email",
	"RoomId", 
	"RoomName", "maxUsers", "questionCount", "answerTimeout"
};

enum fieldsIndices 
{
	USERNAME = 0, PASSWORD, EMAIL, 
	ROOM_ID,
	ROOM_NAME, MAX_USERS, QUESTIONS_COUNT, ANS_TIMEOUT
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;

	RoomData getRoomData()
	{
		return RoomData
		{
			0,
			roomName,
			maxUsers,
			answerTimeout,
			0
		};
	}
};

class JsonRequestPacketDeserializer
{
public: 
	static LoginRequest deserializeLoginRequest(std::vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<uint8_t> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<uint8_t> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<uint8_t> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<uint8_t> buffer);
};

