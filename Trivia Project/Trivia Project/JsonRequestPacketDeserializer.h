#pragma once
#include <iostream>
#include <iomanip>
#include "IRequestHandler.h"

#include "include/nlohmann/json.hpp"
using json = nlohmann::json;

/* Easy access to the json fields. */
static const char* fields[] = { "username", "password", "email" };
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
	static LoginRequest deserializeLoginRequest(std::vector<uint8_t> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<uint8_t> buffer);
};

