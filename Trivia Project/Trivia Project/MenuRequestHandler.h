#pragma once
#include "LoggedUser.h"
#include "JsonRequestPacketDeserializer.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(std::string username, RequestHandlerFactory *m_handlerFactory);
	~MenuRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info, SOCKET socket);
	RequestResult getPlayersInRoom(RequestInfo info);

private:
	LoggedUser * m_user;
	RequestHandlerFactory  m_handlerFactory;

	RequestResult logout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getStatistics(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
};

