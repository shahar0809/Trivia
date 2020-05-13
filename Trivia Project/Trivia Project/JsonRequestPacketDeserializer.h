#pragma once
#include <iostream>
struct LoginRequest
{
	std::string userName;
	std::string password;
};
struct SignupRequest
{
	std::string userName;
	std::string password;
	std::string email;
};
class JsonRequestPacketDeserializer
{
public: 
	static LoginRequest  deserializeLoginRequest(std::string buffer);
	static SignupRequest  deserializeSignupRequest(std::string buffer);
};

