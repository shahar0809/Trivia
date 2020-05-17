#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <sstream>
#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	// Create data using json
	json j;
	j[ERROR_FIELD] = error.message;
	return JsonResponsePacketSerializer::serializeResponse(j, ERROR_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = login.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LOGIN_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = signUp.status;
	return JsonResponsePacketSerializer::serializeResponse(j, SIGN_UP_CODE);
}

Buffer JsonResponsePacketSerializer::serializeResponse(json j, int code)
{
	// Convert the data to binary values.
	std::vector<uint8_t> binData = json::to_cbor(j);
	std::ostringstream os;
	os << std::setw(DATA_LEN_BYTES) << std::setfill('0') << binData.size();
	unsigned char* val = new unsigned char[DATA_LEN_BYTES+1];
	strcpy((char*)val, os.str().c_str());

	//Insert values to the buffer that will be sent to the client.
	Buffer buffer{code,val,binData};
	return buffer;
}
