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
	json j;
	j[jsonFields[STATUS]] = logout.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LOGOUT_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomResponse getRoom)
{
	json j;
	j[jsonFields[STATUS]] = getRoom.status;
	return JsonResponsePacketSerializer::serializeResponse(j, GET_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoom)
{
	std::string playersInRoom = parseVector(getPlayersInRoom.players, DELIMETER);
	json j;
	j[jsonFields[PLAYERS_IN_ROOM]] = playersInRoom;
	return JsonResponsePacketSerializer::serializeResponse(j, GET_PLAYERS_IN_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoom)
{
	json j;
	j[jsonFields[STATUS]] = joinRoom.status;
	return JsonResponsePacketSerializer::serializeResponse(j, JOIN_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoom)
{
	json j;
	j[jsonFields[STATUS]] = createRoom.status;
	return JsonResponsePacketSerializer::serializeResponse(j, CREATE_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse getStatistics)
{
	json j;
	j[jsonFields[STATUS]] = getStatistics.status;
	return JsonResponsePacketSerializer::serializeResponse(j, GET_STATISTICS_CODE);
}

std::string JsonResponsePacketSerializer::parseVector(std::vector<std::string> vec, std::string delimeter)
{
	std::string parsedVec;

	for (auto element : vec)
	{
		parsedVec += element + delimeter;
	}

	// Returning the parsed string without the last char (extra delimeter)
	return parsedVec.substr(parsedVec.size() - 1);
}