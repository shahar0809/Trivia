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
	std::ostringstream streamCode;
	std::ostringstream streamDataLen;

	streamCode << std::setw(CODE_LEN_IN_BYTES) << std::setfill('0') << std::to_string(code);

	streamDataLen << std::setw(DATA_LEN_IN_BYTES) << std::setfill('0') << binData.size();

	return streamCode.str() + streamDataLen.str() + j.dump();
}

std::string JsonResponsePacketSerializer::serializeResponse(LogoutResponse logout)
{
	json j;
	j[jsonFields[STATUS]] = logout.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LOGOUT_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetRoomResponse getRooms)
{
	json j_vec(getRooms.rooms);
	json j;
	j[jsonFields[STATUS]] = getRooms.status;
	j[jsonFields[ROOMS]] = j_vec;
 	return JsonResponsePacketSerializer::serializeResponse(j, GET_ROOMS_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoom)
{
	json players(getPlayersInRoom.players);
	json j;
	j[jsonFields[STATUS]] = getPlayersInRoom.status;
	j[jsonFields[PLAYERS_IN_ROOM]] = players;
	return JsonResponsePacketSerializer::serializeResponse(j, GET_PLAYERS_IN_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoom)
{
	json j;
	j[jsonFields[STATUS]] = joinRoom.status;
	j[jsonFields[ROOM_ID]] = joinRoom.roomData.id;
	j[jsonFields[ROOM_NAME]] = joinRoom.roomData.name;
	j[jsonFields[MAX_USERS]] = joinRoom.roomData.maxPlayers;
	j[jsonFields[QUESTIONS_COUNT]] = joinRoom.roomData.numOfQuestions;
	j[jsonFields[ANS_TIMEOUT]] = joinRoom.roomData.timeForQuestion;
	j[jsonFields[IS_ACTIVE]] = joinRoom.roomData.isActive;
	return JsonResponsePacketSerializer::serializeResponse(j, JOIN_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoom)
{
	json j;
	j[jsonFields[STATUS]] = createRoom.status;
	j[jsonFields[ROOM_ID]] = createRoom.roomId;
	return JsonResponsePacketSerializer::serializeResponse(j, CREATE_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse getStatistics)
{
	json j;
	j[jsonFields[STATUS]] = getStatistics.status;
	j[jsonFields[USER_STATS]] = getStatistics.userStatistics;
	j[jsonFields[HIGH_SCORES]] = json(getStatistics.highScore);
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
	return parsedVec.substr(0, parsedVec.size() - 1);
}

std::string JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoom)
{
	json j;
	j[jsonFields[STATUS]] = closeRoom.status;
	return JsonResponsePacketSerializer::serializeResponse(j, CLOSE_ROOM_CODE);
}
std::string JsonResponsePacketSerializer::serializeResponse(StartGameResponse startGame)
{
	json j;
	j[jsonFields[STATUS]] = startGame.status;
	return JsonResponsePacketSerializer::serializeResponse(j, START_GAME_CODE);
}
std::string JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomState)
{
	json j;
	j[jsonFields[STATUS]] = getRoomState.status;
	j[jsonFields[ANS_TIMEOUT]] = getRoomState.answerTimeout;
	j[jsonFields[PLAYERS_IN_ROOM]] = json(getRoomState.players); 
	j[jsonFields[QUESTIONS_COUNT]] = getRoomState.questionsCount;
	j[jsonFields[IS_ACTIVE]] = getRoomState.hasGameBegun;
	return JsonResponsePacketSerializer::serializeResponse(j, GET_ROOM_STATE_CODE);
	
}

std::string JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoom)
{
	json j;
	j[jsonFields[STATUS]] = leaveRoom.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LEAVE_ROOM_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse getGameResults)
{
	json j;
	j[jsonFields[STATUS]] = getGameResults.status;
	std::vector<std::string> results;

	for (auto user : getGameResults.results)
	{
		results.push_back(user.toString());
	}
	j[jsonFields[RESULTS]] = json(results);
	return JsonResponsePacketSerializer::serializeResponse(j, GET_GAME_RESULTS_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswer)
{
	json j;
	j[jsonFields[STATUS]] = submitAnswer.status;
	j[jsonFields[CORRECT_ANS_ID]] = submitAnswer.correctAnswerId;
	return JsonResponsePacketSerializer::serializeResponse(j, SUBMIT_ANS_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestion)
{
	json j;
	j[jsonFields[STATUS]] = getQuestion.status;
	j[jsonFields[QUESTION]] = getQuestion.question;
	j[jsonFields[ANSWERS]] = json(getQuestion.answers);
	return JsonResponsePacketSerializer::serializeResponse(j, GET_QUESTION_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leaveGame)
{
	json j;
	j[jsonFields[STATUS]] = leaveGame.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LEAVE_GAME_CODE);
}