#pragma once
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
struct Buffer
{
	int id;
	int len;
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
