#pragma once
#include "RoomMemberRequestHandler.h"

class RoomAdminRequestHandler : public RoomMemberRequestHandler
{
public:
	RoomAdminRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

	RequestResult leaveRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult closeRoom(RequestInfo info);
};

