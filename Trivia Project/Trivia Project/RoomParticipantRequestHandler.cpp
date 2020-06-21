#include "RoomParticipantRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RoomParticipantRequestHandler::RoomParticipantRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManager;
}

RequestResult RoomParticipantRequestHandler::getRoomState(RequestInfo info)
{
	RoomData roomData = m_room.getMetadata();

	// I'm not sure when the status is FAILED

	GetRoomStateResponse resp
	{
		SUCCEEDED,
		m_room.getHasGameBegun(),
		m_room.getAllUsernames(),
		roomData.numOfQuestions,
		roomData.timeForQuestion
	};

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeGetRoomStateResponse(resp), nullptr
	};
}

RequestResult RoomParticipantRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult res = this->m_handlerFactory.createMenuRequestHandler(m_user)->getPlayersInRoom(info);
	res.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager);
	return res;
}

