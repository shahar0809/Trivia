#include "JsonRequestPacketDeserializer.h"

/**
* Deserializes a logIn request.
* @param buffer: a swquence of bytes that represent the data (json format).
* return: a Login Request, that contains the data.
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	// Getting the data from the packet
	json j = json::parse(buffer);

	// Printing json fields (to make sure that the data transformation is valid).
	std::cout <<
		"Log In request:" << std::endl <<
		"Username: " << j[fields[USERNAME]] << std::endl <<
		"Password: " << j[fields[PASSWORD]] << std::endl << std::endl;

	return LoginRequest{ j[fields[USERNAME]], j[fields[PASSWORD]]};
}

/**
* Deserializes a signUp request.
* @param buffer: a swquence of bytes that represent the data (json format).
* return: a SignUp Request, that contains the data.
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	// Getting the data from the packet
	json j = json::parse(buffer);

	// Printing json fields (to make sure that the data transformation is valid.
	std::cout << 
		"Sign Up request:" << std::endl <<
		"Username: " << j[fields[USERNAME]] << std::endl <<
		"Password: " << j[fields[PASSWORD]] << std::endl <<
		"Email: " << j[fields[EMAIL]] << std::endl << std::endl;

	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer);	 

	// Printing json fields (to make sure that the data transformation is valid).
	std::cout <<
		"Get Players In Room Request:" << std::endl <<
		"Room ID: " << j[jsonFields[ROOM_ID]] << std::endl << std::endl;

	return GetPlayersInRoomRequest{ j[jsonFields[ROOM_ID]] };
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer);

	// Printing json fields (to make sure that the data transformation is valid).
	std::cout <<
		"Join Room Request:" << std::endl <<
		"Room ID: " << j[jsonFields[ROOM_ID]] << std::endl << std::endl;

	return JoinRoomRequest{ j[jsonFields[ROOM_ID]] };
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<uint8_t> buffer)
{
	json j = json::parse(buffer);
	
	// Printing json fields (to make sure that the data transformation is valid).
	std::cout <<
		"Create Room Request:" << std::endl <<
		"Room Name: " << j[fields[USERNAME]] << std::endl <<
		"Max Amount of Users: " << j[fields[PASSWORD]] << std::endl <<
		"Questions Count: " << j[fields[EMAIL]] << std::endl <<
		"Answer Time out: " << j[fields[PASSWORD]] << std::endl << std::endl;

	return CreateRoomRequest 
	{
		j[jsonFields[ROOM_NAME]],
		j[jsonFields[MAX_USERS]],
		j[jsonFields[QUESTIONS_COUNT]],
		j[jsonFields[ANS_TIMEOUT]] 
	};
}