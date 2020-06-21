#include "RoomAdminRequestHandler.h"



RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager) :
	RoomParticipantRequestHandler(room, user, handlerFactory, roomManager)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return (info.requestId >= CLOSE_ROOM_CODE && info.requestId <= GET_ROOM_STATE_CODE) || info.requestId == GET_PLAYERS_IN_ROOM_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
		case CLOSE_ROOM_CODE:
			return closeRoom(info);

		case START_GAME_CODE:
			return startGame(info);

		case GET_ROOM_STATE_CODE:
			return getRoomState(info);

		case GET_PLAYERS_IN_ROOM_CODE:
		{
			RequestResult res = this->m_handlerFactory.createMenuRequestHandler(m_user->getUsername())->getPlayersInRoom(info);
			res.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager);
			return res;
		}
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	// Assuming that in the client side, the admin already calls leaveRoom for every member, so that the only player in the room is the admin.
	CloseRoomResponse resp;

	// Removing last player from the room
	if (this->m_room.removeUser(*(this->m_user)))
	{
		// Removing all the players from the room
		for (auto user : m_room.getAllUsers())
		{
			// Remove the current player from the room.
		}

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
		this->m_handlerFactory.createMenuRequestHandler(this->m_user->getUsername())
	};
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	// Once GameManger is implemented -> we call it to actually start the game.
	StartGameResponse resp{ SUCCEEDED };

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeStartGameResponse(resp),
		this->m_handlerFactory.createRoomAdminRequestHandler(
			this->m_room,
			this->m_user,
			&this->m_handlerFactory,this->m_roomManager)
	};
}