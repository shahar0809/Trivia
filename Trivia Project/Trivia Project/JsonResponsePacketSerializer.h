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

struct Buffer
{
	unsigned char code;
	unsigned char* dataLen;
	std::vector<uint8_t> data;
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

class JsonResponsePacketSerializer
{
public:
	//all these functions retruns buffer
	static Buffer serializeResponse(ErrorResponse);
	static Buffer serializeResponse(LoginResponse);
	static Buffer serializeResponse(SignupResponse);

private:
	static Buffer serializeResponse(json j, int code);
};
