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