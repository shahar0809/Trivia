#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <sstream>
#include "JsonResponsePacketSerializer.h"

std::string JsonResponsePacketSerializer::serializeResponse(ErrorResponse error)
{
	// Create data using json
	json j;
	j[ERROR_FIELD] = error.message;
	return JsonResponsePacketSerializer::serializeResponse(j, ERROR_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(LoginResponse login)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = login.status;
	return JsonResponsePacketSerializer::serializeResponse(j, LOGIN_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(SignupResponse signUp)
{
	// Create data using json
	json j;
	j[ORDINARY_RESPONSE_FIELD] = signUp.status;
	return JsonResponsePacketSerializer::serializeResponse(j, SIGN_UP_CODE);
}

std::string JsonResponsePacketSerializer::serializeResponse(json j, int code)
{
	// Convert the data to binary values.
	std::vector<uint8_t> binData = json::to_cbor(j);
	std::ostringstream os;
	os << std::setw(DATA_LEN_IN_BYTES) << std::setfill('0') << binData.size();
	unsigned char* dataLen = new unsigned char[DATA_LEN_IN_BYTES +1];
	strcpy((char*)dataLen, os.str().c_str());

	std::string headers(1, static_cast<unsigned char>(code));
	headers += reinterpret_cast<char const*>(dataLen);
	std::string data(binData.begin(), binData.end());
	return headers+data;
}
