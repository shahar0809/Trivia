#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	//MenuRequestHandler();
	MenuRequestHandler(std::string username, RequestHandlerFactory *m_handlerFactory);
	~MenuRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

private:
	LoggedUser * m_user;
	RequestHandlerFactory  m_handlerFactory;

	RequestResult logout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getStatistics(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
	RequestResult leaveRoom(RequestInfo info);
};

