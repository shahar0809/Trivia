#include "RoomMemberRequestHandler.h"


/*
 *** SAME CODE AS RoomAdmin.
  We can create a class that roomAdmin and roomMember inherit from, and implemnet the common methods there.
*/
RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser* user, RequestHandlerFactory* handlerFactory, RoomManager* roomManger)
{
	this->m_room = room;
	m_user = user;
	m_handlerFactory = *handlerFactory;
	m_roomManager = roomManger;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= LEAVE_ROOM_CODE && info.requestId <= GET_ROOM_STATE_CODE || info.requestId == GET_PLAYERS_IN_ROOM_CODE;
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

	case GET_PLAYERS_IN_ROOM_CODE:
	{
		RequestResult res = this->m_handlerFactory.createMenuRequestHandler(this->m_user->getUsername())->getPlayersInRoom(info);;
		res.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room,
			this->m_user, &this->m_handlerFactory, this->m_roomManager);
		return res;
	}
		
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
		this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room,
		this->m_user,&this->m_handlerFactory,this->m_roomManager)
	};
}

RequestResult RoomMemberRequestHandler::startGame(RequestInfo info)
{
	// Once GameManger is implemented -> we call it to actually start the game.
	StartGameResponse resp{ SUCCEEDED };
	m_room.setHasGameBegun(true);

	return RequestResult
	{ 
		JsonResponsePacketSerializer::serializeStartGameResponse(resp),
		this->m_handlerFactory.createRoomMemberRequestHandler(this->m_room,
		this->m_user,&this->m_handlerFactory,this->m_roomManager)
	};
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
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
		this->m_handlerFactory.createRoomMemberRequestHandler(
			this->m_room,this->m_user,&this->m_handlerFactory,this->m_roomManager)
	};
}
