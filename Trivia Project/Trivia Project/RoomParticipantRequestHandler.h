#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"

class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RoomParticipantRequestHandler : public IRequestHandler
{
public:
	RoomParticipantRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	virtual RequestResult handleRequest(RequestInfo info) = 0;
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult getRoomState(RequestInfo info) = 0;
	virtual RequestResult getPlayersInRoom(RequestInfo info) = 0;

protected:
	Room* m_room;
	LoggedUser* m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory m_handlerFactory;
};

