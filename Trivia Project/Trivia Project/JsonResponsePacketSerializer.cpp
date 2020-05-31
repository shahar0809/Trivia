#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <sstream>
#include "JsonResponsePacketSerializer.h"

std::string JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	// Create data using json
	json j;
	j[ERROR_FIELD] = error.message;
	return JsonResponsePacketSerializer::serializeResponse(j, ERROR_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = std::to_string(login.status);
	return JsonResponsePacketSerializer::serializeResponse(j, LOGIN_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = std::to_string(signUp.status);
	return JsonResponsePacketSerializer::serializeResponse(j, SIGN_UP_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(json j, int code)
{
	std::string binJson = j.dump(); // Getting the json as a string
	std::vector<unsigned char> binData(binJson.begin(), binJson.end()); 
	std::ostringstream stream;

	stream << std::setw(DATA_LEN_IN_BYTES) << std::setfill('0') << binData.size();

	return std::to_string(code) + stream.str() + j.dump();
}

std::string JsonResponsePacketSerializer::serializeResponse(LogoutResponse logout)
{
	return "h";
}
std::string JsonResponsePacketSerializer::serializeResponse(GetRoomResponse getRoom)
{
	return "h";
}
std::string JsonResponsePacketSerializer::serializerResponse(GetPlayersInRoomResponse getPlayersInRoom)
{
	return "h";
}
std::string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoom)
{
	return "h";
}
std::string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoom)
{
	return "h";
}
std::string JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse getStatistics)
{
	return "h";
}