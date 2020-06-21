#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"

class RoomMemberRequestHandler;
class RoomAdminRequestHandler;

class RoomParticipantRequestHandler : public IRequestHandler
{
public:
	RoomParticipantRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager);

	virtual bool isRequestRelevant(RequestInfo info) = 0;

	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

protected:
	Room m_room;
	LoggedUser* m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory m_handlerFactory;
};

