
#include <sstream> 
#include "JsonResponsePacketSerializer.h"

#define ERROR_FIELD "message"
#define ORDINARY_RESPONSE_FIELD "status"
#define ERROR_CODE 0
#define LOGIN_CODE 1
#define SIGN_UP_CODE 2

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	//Create data using json
	json j;
	j[ERROR_FIELD] = error.message;
	return JsonResponsePacketSerializer::serializeResponse(j, ERROR_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	//Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = login.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LOGIN_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	//Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = signUp.status;
	return JsonResponsePacketSerializer::serializeResponse(j, SIGN_UP_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(json j, int code)
{
	std::string str = j.dump();

	//Convert the data to bin values.
	std::vector<uint8_t> binData = json::to_cbor(j);

	//Insert values to the buffer that will be sent to the client.
	Buffer buffer{ code, binData.size(),binData};
	return buffer;
}
