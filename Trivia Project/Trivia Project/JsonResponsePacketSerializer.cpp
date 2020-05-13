#include <iostream>
#include "JsonResponsePacketSerializer.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define ERROR_FIELD "message"
#define ORDINARY_RESPONSE_FIELD "status"
#define ERROR_CODE 0
#define LOGIN_CODE 1
#define SIGN_UP_CODE 2

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	json j;
	j[ERROR_FIELD] = error.message;
	Buffer buffer{ ERROR_CODE ,j.dump().length(),j.dump() };
	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	json j;
	j[ORDINARY_RESPONSE_FIELD] = login.status;
	Buffer buffer{ LOGIN_CODE ,j.dump().length(),j.dump()};
	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	json j;
	j[ORDINARY_RESPONSE_FIELD] = signUp.status;
	Buffer buffer{ SIGN_UP_CODE ,j.dump().length(),j.dump() };
	return buffer;
}