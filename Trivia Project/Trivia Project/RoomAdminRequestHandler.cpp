#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManger;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= LEAVE_ROOM_CODE && info.requestId <= GET_ROOM_STATE_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
	case CLOSE_ROOM_CODE:
		closeRoom(info);
		break;

	case START_GAME_CODE:
		startGame(info);
		break;

	case GET_ROOM_STATE_CODE:
		getRoomState(info);
		break;
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	// Assuming that in the client side, the admin already calls leaveRoom for every member, so that the only player in the room is the admin.
	CloseRoomResponse resp;

	// Removing last player from the room
	if (this->m_room.removeUser(*(this->m_user)))
	{
		m_roomManager->deleteRoom(m_room.getMetadata().id); // Deleting the room
		resp.status = SUCCEEDED;
	}
	else
	{
		resp.status = FAILED;
	}
	
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeCloseRoomResponse(resp),
		this->m_handlerFactory.createRoomMemberRequestHandler()
	};
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	// Once GameManger is implemented -> we call it to actually start the game.
	StartGameResponse resp{ SUCCEEDED };
	m_room.setHasGameBegun(true);

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeStartGameResponse(resp),
		this->m_handlerFactory.createRoomMemberRequestHandler()
	};
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
	RoomData roomData = m_room.getMetadata();

	// Also, I'm not sure when the status is FAILED

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
		this->m_handlerFactory.createRoomMemberRequestHandler()
	};
}

