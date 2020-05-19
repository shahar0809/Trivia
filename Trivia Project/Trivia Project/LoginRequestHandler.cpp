#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LOGIN_CODE || info.requestId == SIGN_UP_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	if (info.requestId == LOGIN_CODE)
	{
		JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		LoginResponse response = { 1 };
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response) };
	}
	else if (info.requestId == SIGN_UP_CODE)
	{
		JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
		SignupResponse response = { 1 };
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response) };
	}
}
