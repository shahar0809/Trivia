#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo)
{
	RequestResult res;
	return res;
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::getStatistics(RequestInfo info)
{
	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	RequestResult res;
	return res;
}