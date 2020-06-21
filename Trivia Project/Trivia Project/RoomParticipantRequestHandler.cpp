#include "RoomParticipantRequestHandler.h"

RoomParticipantRequestHandler::RoomParticipantRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManager;
}

RequestResult RoomParticipantRequestHandler::startGame(RequestInfo info)
{
	// Once GameManger is implemented -> we call it to actually start the game.
	StartGameResponse resp{ SUCCEEDED };

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeStartGameResponse(resp),
		this->m_handlerFactory.createRoomMemberRequestHandler(
			this->m_room,
			this->m_user, 
			&this->m_handlerFactory,this->m_roomManager)
	};
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
		JsonResponsePacketSerializer::serializeGetRoomStateResponse(resp),
		this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room,this->m_user,&this->m_handlerFactory,this->m_roomManager)
	};
}

