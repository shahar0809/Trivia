#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(std::string username, RequestHandlerFactory* m_handlerFactory)
{
	this->m_handlerFactory = *m_handlerFactory;
	this->m_user = new LoggedUser(username);
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= CREATE_ROOM_CODE && info.requestId <= LEAVE_ROOM_CODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	switch (info.requestId)
	{
		case CREATE_ROOM_CODE:
		{
			return this->createRoom(info);
		}
		case GET_ROOMS_CODE:
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
		case LEAVE_ROOM_CODE:
		{
			return RequestResult{};
		}
	}
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	LogoutResponse resp;
	if (this->m_handlerFactory.getLoginManger().logout(this->m_user->getUsername()))
	{
		resp.status = SUCCEEDED;
	}
	else
	{
		resp.status = FAILED;
	}

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),nullptr
	};
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	RoomManager* roomManager = m_handlerFactory.getRoomManager();
	std::vector<std::string> roomNames;

	for (auto room : roomManager->getRooms())
	{
		roomNames.push_back(room.name + "," + std::to_string(room.id));
	}
	GetRoomResponse resp{ SUCCEEDED, roomNames };
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		m_handlerFactory.createMenuRequestHandler(this->m_user->getUsername())
	};
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	RoomManager* roomManager = m_handlerFactory.getRoomManager();
	std::vector<LoggedUser> loggedUsers = roomManager->getRoom(req.roomId)->getAllUsers();
	std::vector<std::string> roomPlayers;

	for (auto user : loggedUsers)
	{
		roomPlayers.push_back(user.getUsername());
	}

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse { roomPlayers }),
		m_handlerFactory.createMenuRequestHandler(this->m_user->getUsername())
	};
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo info)
{
	StatisticsManager& statsManager = this->m_handlerFactory.getStatisticsManager();
	GetStatisticsResponse resp;
	std::pair<UserStatistics, std::vector<Score>> stats;

	try
	{
		stats= statsManager.getStatistics(this->m_user->getUsername());
	}
	catch (const std::exception& e)
	{
		resp.status = FAILED;
		return RequestResult{ JsonResponsePacketSerializer::serializeResponse(resp), nullptr };
	}

	std::vector<std::string> highScore;

	for (auto score : stats.second)
		highScore.push_back(score.toString());

	resp.highScore = highScore;
	resp.userStatistics = stats.first.toString();
	resp.status = SUCCEEDED;

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		m_handlerFactory.createMenuRequestHandler(this->m_user->getUsername())
	};

}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomRequest joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	RoomManager* roomManager = m_handlerFactory.getRoomManager();

	JoinRoomResponse resp;
	resp.roomData = roomManager->getRoom(joinReq.roomId)->getMetadata();

	if (!(roomManager->getRoom(joinReq.roomId)->addUser(*(this->m_user))))
	{
		resp.status = FAILED;
	}
	else
	{
		resp.status = SUCCEEDED;
	}

	return RequestResult{ JsonResponsePacketSerializer::serializeResponse(resp),
		m_handlerFactory.createRoomMemberRequestHandler(*this->m_handlerFactory.getRoomManager()->getRoom(joinReq.roomId),
			this->m_user,&this->m_handlerFactory,this->m_handlerFactory.getRoomManager())};
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomRequest createReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	RoomManager* roomManager = m_handlerFactory.getRoomManager();
	CreateRoomResponse resp;
	Room* room = nullptr;

	try
	{
		room = roomManager->createRoom(*m_user, createReq.getRoomData());

	}
	catch (const std::exception & e)
	{
		resp.status = FAILED;
		return RequestResult
		{ 
			JsonResponsePacketSerializer::serializeResponse(resp),
			m_handlerFactory.createRoomAdminRequestHandler(*room, m_user, &m_handlerFactory, m_handlerFactory.getRoomManager())
		};
	}
	
	resp.status = SUCCEEDED;
	resp.roomId = roomManager->getLastId();
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		m_handlerFactory.createRoomAdminRequestHandler(*room, m_user, &m_handlerFactory, m_handlerFactory.getRoomManager())
	};
}

