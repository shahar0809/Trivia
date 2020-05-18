#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	return LoginRequest{ j[fields[USERNAME]], j[fields[PASSWORD]]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<uint8_t> buffer)
{
	json j = getJson(buffer);
	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

json JsonRequestPacketDeserializer::getJson(std::vector<uint8_t> packet)
{
	return json::from_cbor(packet);
}