#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

	RequestResult leaveRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

protected:
	Room m_room;
	LoggedUser* m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory m_handlerFactory;
};

