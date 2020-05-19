#include "JsonRequestPacketDeserializer.h"
#include <iostream>
#include <iomanip>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	std::cout << "data received:\n" << "Username: " << j[fields[USERNAME]] << ", Password: " << j[fields[PASSWORD]] << std::endl;
	return LoginRequest{ j[fields[USERNAME]], j[fields[PASSWORD]]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	std::cout << "data received:\n" << "Username: " << j[fields[USERNAME]] << ", Password: " << j[fields[PASSWORD]] << 
		", email: " << j[fields[EMAIL]] << std::endl;
	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

json JsonRequestPacketDeserializer::getJson(std::vector<uint8_t> packet)
{
	return json::parse(packet);
}