#pragma once
#include <iostream>
#include <vector>
#include <sstream> 

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

#define ERROR_FIELD "message"
#define ORDINARY_RESPONSE_FIELD "status"
#define DATA_LEN_IN_BYTES 4

enum Codes { ERROR_CODE = 0, LOGIN_CODE, SIGN_UP_CODE };

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

class JsonResponsePacketSerializer
{
public:
	//all these functions retruns buffer
	static std::string serializeResponse(ErrorResponse error);
	static std::string serializeResponse(LoginResponse login);
	static std::string serializeResponse(SignupResponse signUp);

private:
	static std::string serializeResponse(json j, int code);
};
