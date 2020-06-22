#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::MenuRequestHandler(std::string username)
{
	this->m_user = LoggedUser(username);
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= CREATE_ROOM_CODE && info.requestId <= LOGOUT_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
		case CREATE_ROOM_CODE:
		{
			return this->createRoom(info);
		}
		case GET_ROOM_CODE:
		{
			return this->getRooms(info);
		}
		case GET_PLAYERS_IN_ROOM_CODE:
		{
			return this->getPlayersInRoom(info);
		}
		case JOIN_ROOM_CODE:
		{
			return this->joinRoom(info);
		}
		case GET_STATISTICS_CODE:
		{
			return this->getStatistics(info);
		}
		case LOGOUT_CODE:
		{
			return this->logout(info);
		}
	}
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	RequestResult res;
	return res;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	RoomManager roomManager = m_handlerFactory.getRoomManager();

	GetRoomResponse resp{ 1, roomManager.getRooms() };
	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(resp), nullptr };
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	RoomManager roomManager = m_handlerFactory.getRoomManager();
	
	return RequestResult{ "", nullptr };
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo info)
{
	StatisticsManager statsManager = this->m_handlerFactory.getStatisticsManager();
	GetStatisticsResponse resp;

	try
	{
		std::pair<UserStatistics, std::vector<Score>> stats = statsManager.getStatistics(this->m_user.getUsername());
	}
	catch (const std::exception& e)
	{
		resp.status = FAILED;
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(resp), nullptr };
	}
	
	resp.status = SUCCEEDED;
	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(resp), nullptr };
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	RoomManager roomManager = m_handlerFactory.getRoomManager();

	RequestResult res;
	return res;
}
RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomRequest createReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	RoomManager roomManager = m_handlerFactory.getRoomManager();
	
	roomManager.createRoom(m_user, createReq.getRoomData());
	RequestResult res;
	return res;
}