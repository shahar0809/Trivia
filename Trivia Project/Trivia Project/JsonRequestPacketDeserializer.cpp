#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <iomanip>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	std::cout << "Login Request:\n" << "Username: " << j[fields[USERNAME]] << "\nPassword: " << j[fields[PASSWORD]] << std::endl << std::endl;
	return LoginRequest{ j[fields[USERNAME]], j[fields[PASSWORD]]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	std::cout << "Sign Up request:\n" << "Username: " << j[fields[USERNAME]] << "\nPassword: " << j[fields[PASSWORD]] << 
		"\nemail: " << j[fields[EMAIL]] << std::endl << std::endl;
	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

json JsonRequestPacketDeserializer::getJson(std::vector<uint8_t> packet)
{
	return json::parse(packet);
}