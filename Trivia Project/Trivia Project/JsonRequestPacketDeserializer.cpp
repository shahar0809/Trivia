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
	std::cout << "Login Request:\n" << 
		"Username: " << j[fields[USERNAME]] << 
		"\nPassword: " << j[fields[PASSWORD]] << std::endl << std::endl;

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
	std::cout << "Sign Up request:\n" << 
		"Username: " << j[fields[USERNAME]] << 
		"\nPassword: " << j[fields[PASSWORD]] << 
		"\nEmail: " << j[fields[EMAIL]] << std::endl << std::endl;

	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<uint8_t> buffer)
{
	GetPlayersInRoomRequest g{ 1 };
	return g;
}
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<uint8_t> buffer)
{
	JoinRoomRequest g{ 1 };
	return g;
}
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<uint8_t> buffer)
{
	CreateRoomRequest g{ "F",1,1,1 };
	return g;
}