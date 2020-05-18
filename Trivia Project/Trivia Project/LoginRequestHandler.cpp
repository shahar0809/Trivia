#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LOGIN_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

	if (info.requestId == LOGIN_CODE)
	{
		LoginResponse response = { 1 };
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response) };
	}
	else if (info.requestId == SIGN_UP_CODE)
	{
		SignupResponse response = { 1 };
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response) };
	}
}
