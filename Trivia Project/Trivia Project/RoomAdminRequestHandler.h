#pragma once
#include "RoomParticipantRequestHandler.h"

class RoomAdminRequestHandler : public RoomParticipantRequestHandler
{
public:
	RoomAdminRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info, SOCKET socket);

	RequestResult startGame(RequestInfo info);
	RequestResult closeRoom(RequestInfo info);
};

