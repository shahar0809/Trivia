#pragma once
#include <thread>
#include "RoomParticipantRequestHandler.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public RoomParticipantRequestHandler
{
public:
	RoomMemberRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult leaveRoom(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
};

