#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::string buffer)
{
	json j = getJson(buffer);
	return LoginRequest{ j[fields[USERNAME]], j[fields[PASSWORD]]};
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::string buffer)
{
	json j = getJson(buffer);
	return SignupRequest{ j[fields[USERNAME]], j[fields[PASSWORD]], j[fields[EMAIL]] };
}

json getJson(std::string buffer)
{
	/* I'm not sure that we need to get dataLength here. */
	std::vector<uint8_t> packet(buffer.begin() + 4, buffer.end()); // Getting the json field from the packet as bytes.
	return json::from_cbor(packet);
}