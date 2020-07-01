#pragma once
#include "RoomParticipantRequestHandler.h"
#include "GameRequestHandler.h"

class RoomAdminRequestHandler : public RoomParticipantRequestHandler
{
public:
	RoomAdminRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult closeRoom(RequestInfo info);
};

