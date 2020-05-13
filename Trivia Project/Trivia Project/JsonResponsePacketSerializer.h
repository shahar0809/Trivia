#pragma once
#include <iostream>
#include <vector>
struct Buffer
{
	int id;
	int len;
	std::string data;
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
};
