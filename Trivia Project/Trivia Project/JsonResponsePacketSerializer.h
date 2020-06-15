#pragma once
#include <iostream>
#include <vector>
#include <sstream> 
#include <bitset>
#include "Helper.h"
#include "Room.h"
#include "JsonRequestPacketDeserializer.h"

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

#define ERROR_FIELD "message"
#define ORDINARY_RESPONSE_FIELD "status"
#define DELIMETER ","

enum Codes 
{ 
	ERROR_CODE = 0, LOGIN_CODE, SIGN_UP_CODE, CREATE_ROOM_CODE, 
	GET_ROOMS_CODE, GET_PLAYERS_IN_ROOM_CODE,
	JOIN_ROOM_CODE, GET_STATISTICS_CODE, LOGOUT_CODE, LEAVE_ROOM_CODE
};

struct ErrorResponse
{
	std::string message;
};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomResponse
{
	unsigned int status;
	std::vector<std::string> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;
};

struct JoinRoomResponse
{
	unsigned int status;
	RoomData roomData;
};

struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

struct GetStatisticsResponse
{
	unsigned int status;
	std::string userStatistics;
	std::vector<std::string> highScore;
};

class JsonResponsePacketSerializer
{
public:
	static std::string serializeResponse(ErrorResponse error);
	static std::string serializeResponse(LoginResponse login);
	static std::string serializeResponse(SignupResponse signUp);
	static std::string serializeResponse(LogoutResponse logout);
	static std::string serializeResponse(GetRoomResponse getRoom);
	static std::string serializeResponse(GetPlayersInRoomResponse getPlayersInRoom);
	static std::string serializeResponse(JoinRoomResponse joinRoom);
	static std::string serializeResponse(CreateRoomResponse createRoom);
	static std::string serializeResponse(GetStatisticsResponse getStatistics);

private:
	static std::string serializeResponse(json j, int code);

	static std::string parseVector(std::vector<std::string> vec, std::string delimeter);
};