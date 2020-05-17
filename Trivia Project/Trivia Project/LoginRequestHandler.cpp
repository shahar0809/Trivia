#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LOGIN_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	LoginResponse response = { 1 };
	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(response) };
}
