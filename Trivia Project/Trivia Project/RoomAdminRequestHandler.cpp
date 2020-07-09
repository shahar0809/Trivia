#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManager) :
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
			return getPlayersInRoom(info);
	}
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
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
			JsonResponsePacketSerializer::serializeResponse(resp),
			m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager)
		};
	}

	GetRoomStateResponse resp
	{
		SUCCEEDED, roomData.isActive, m_room->getAllUsernames(), roomData.numOfQuestions, roomData.timeForQuestion
	};

	RequestResult res
	{
		JsonResponsePacketSerializer::serializeResponse(resp), nullptr
	};

	if (roomData.isActive)
	{
		res.newHandler = m_handlerFactory.createGameRequestHandler(m_user, &m_handlerFactory);
	}
	else
	{
		res.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager);
	}
	
	return res;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	CloseRoomResponse resp;

	// Removing all the players from the room
	for (auto user : m_room->getAllUsers())
	{
		m_room->removeUser(user);
	}

	m_roomManager->deleteRoom(m_room->getMetadata().id); // Deleting the room
	resp.status = SUCCEEDED;
	
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		this->m_handlerFactory.createMenuRequestHandler(this->m_user)
	};
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	StartGameResponse resp;

	try
	{
		this->m_handlerFactory.getGameManager()->createGame(*m_room);
		m_room->setHasGameBegun(true);
	}
	catch (const std::exception & e)
	{
		resp.status = FAILED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory.createMenuRequestHandler(this->m_user)
		};
	}

	resp.status = SUCCEEDED;
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		this->m_handlerFactory.createGameRequestHandler(this->m_user, &this->m_handlerFactory)
	};
}

RequestResult RoomAdminRequestHandler::getPlayersInRoom(RequestInfo info)
{
	RequestResult res = this->m_handlerFactory.createMenuRequestHandler(m_user)->getPlayersInRoom(info);
	res.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(m_room, m_user, &m_handlerFactory, m_roomManager);
	return res;
}