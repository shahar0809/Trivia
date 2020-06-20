#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager) 
	: RoomParticipantRequestHandler(room, user, handlerFactory, roomManager)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId >= LEAVE_ROOM_CODE && info.requestId <= GET_ROOM_STATE_CODE && info.requestId == CLOSE_ROOM_CODE)
		|| info.requestId == GET_PLAYERS_IN_ROOM_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
		case LEAVE_ROOM_CODE:
			return leaveRoom(info);
		
		case START_GAME_CODE:
			return startGame(info);

		case GET_ROOM_STATE_CODE:
			return getRoomState(info);
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	LeaveRoomResponse resp;

	if (this->m_room.removeUser(*(this->m_user)))
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
		m_handlerFactory.createMenuRequestHandler(m_user->getUsername())
	};
}