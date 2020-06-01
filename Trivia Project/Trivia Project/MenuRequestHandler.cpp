#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::MenuRequestHandler(std::string username)
{
	this->m_user = LoggedUser(username);
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= CREATE_ROOM_CODE && info.requestId <= LOGOUT_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
	case CREATE_ROOM_CODE:
	{
		return this->createRoom(info);
	}
	case GET_ROOM_CODE:
	{
		return this->getRooms(info);
	}
	case GET_PLAYERS_IN_ROOM_CODE:
	{
		return this->getPlayersInRoom(info);
	}
	case JOIN_ROOM_CODE:
	{
		return this->joinRoom(info);
	}
	case GET_STATISTICS_CODE:
	{
		return this->getStatistics(info);
	}
	case LOGOUT_CODE:
	{
		return this->logout(info);
	}
	}
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
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
	StatisticsManager statManager = this->m_handlerFactory.getStatisticsManager();
	statManager.getStatistics(this->m_user.getUsername());
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