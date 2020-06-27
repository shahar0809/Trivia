#pragma once
#include "RoomParticipantRequestHandler.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public RoomParticipantRequestHandler
{
public:
	RoomMemberRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info, SOCKET socket);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult leaveRoom(RequestInfo info);
};

