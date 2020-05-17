#pragma once
#include <iostream>
#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

const char* fields[] = { "username", "password", "email" };
enum fieldsIndices {USERNAME = 0, PASSWORD, EMAIL};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

class JsonRequestPacketDeserializer
{
public: 
	static LoginRequest deserializeLoginRequest(std::string buffer);
	static SignupRequest deserializeSignupRequest(std::string buffer);
};

