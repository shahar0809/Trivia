#include "RoomMemberRequestHandler.h"


RoomMemberRequestHandler::RoomMemberRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager) 
	: RoomParticipantRequestHandler(room, user, handlerFactory, roomManager)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId >= LEAVE_ROOM_CODE && info.requestId <= GET_ROOM_STATE_CODE) || info.requestId == GET_PLAYERS_IN_ROOM_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
		case LEAVE_ROOM_CODE:
			return leaveRoom(info);

		case GET_ROOM_STATE_CODE:
			return getRoomState(info);

		case GET_PLAYERS_IN_ROOM_CODE:
			return getPlayersInRoom(info);
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	LeaveRoomResponse resp;

	if (this->m_room->removeUser(*(this->m_user)))
	{
		resp.status = SUCCEEDED;
	}
	else
	{
		resp.status = FAILED;
	}
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeLeaveRoomResponse(resp),
		m_handlerFactory.createMenuRequestHandler(m_user)
	};
}

RequestResult RoomMemberRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult res = this->m_handlerFactory.createMenuRequestHandler(m_user)->getPlayersInRoom(info);
	res.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager);
	return res;
}