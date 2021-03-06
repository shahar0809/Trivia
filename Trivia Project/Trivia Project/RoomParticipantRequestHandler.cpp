#include "RoomParticipantRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RoomParticipantRequestHandler::RoomParticipantRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManager;
	m_username = user->getUsername();
}

RequestResult RoomParticipantRequestHandler::getRoomState(RequestInfo info)
{
	RoomData roomData;

	try
	{
		roomData = m_room->getMetadata();
	}
	catch (std::exception & e)
	{
		GetRoomStateResponse resp
		{
			FAILED, false, std::vector<std::string>(), 0, 0
		};

		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),nullptr
		};
	}

	GetRoomStateResponse resp
	{
		SUCCEEDED, m_room->getHasGameBegun(), m_room->getAllUsernames(), roomData.numOfQuestions, roomData.timeForQuestion
	};

	RequestResult res
	{
		JsonResponsePacketSerializer::serializeResponse(resp), nullptr
	};


	if (m_room->getHasGameBegun())
	{
		res.newHandler = m_handlerFactory.createGameRequestHandler(m_user, &m_handlerFactory);
	}
	if (!roomData.isActive)
	{
		res.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	}
	return res;
}

