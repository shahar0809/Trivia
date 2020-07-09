#include "RoomParticipantRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RoomParticipantRequestHandler::RoomParticipantRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManager;
}


