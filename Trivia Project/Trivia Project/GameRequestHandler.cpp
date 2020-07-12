#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(LoggedUser* user, RequestHandlerFactory* handlerFactory)
{
	this->m_handlerFactory = handlerFactory;
	this->m_gameManager = handlerFactory->getGameManager();
	this->m_user = user;
	this->m_game = this->m_gameManager->getGame(*user);
	m_username = user->getUsername();
}

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId >= LEAVE_GAME_CODE && info.requestId <= SUBMIT_ANS_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	// Refering the request into the matching function.
	switch (info.requestId)
	{
	case LEAVE_GAME_CODE:
		return leaveGame(info);

	case GET_GAME_RESULTS_CODE:
		return getGameResults(info);

	case GET_QUESTION_CODE:
		return getQuestion(info);

	case SUBMIT_ANS_CODE:
		return submitAnswer(info);
	}
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	LeaveGameResponse resp;
	if (m_handlerFactory->getGameManager()->removePlayer(*m_user))
	{
		if (m_game->getPlayers().size() == 0)
		{
			m_handlerFactory->getGameManager()->deleteGame(*m_user);
		}
		resp.status = SUCCEEDED;
	}
	else
	{
		resp.status = FAILED;
	}

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		this->m_handlerFactory->createGameRequestHandler(m_user, m_handlerFactory)

		/*JsonResponsePacketSerializer::serializeLeaveGameResponse(resp),
		this->m_handlerFactory->createMenuRequestHandler(m_user)*/

	};
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	GameManager* gameManager = m_handlerFactory->getGameManager();
	GetGameResultsResponse resp;

	try
	{
		resp.results = gameManager->getGameResults(*this->m_user);
	}

	// If everyone is not finished yet.
	catch (std::string)
	{
		resp.status = FAILED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory->createGameRequestHandler(m_user, m_handlerFactory)
		};
	}
	catch (const std::exception & e)
	{
		resp.status = FAILED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory->createMenuRequestHandler(m_user)
		};
	}
	try
	{
		this->m_gameManager->getGame(*m_user);
	}
	catch (const std::exception & e)//Case game was deleted, erase room too.
	{
		m_handlerFactory->getRoomManager()->deleteRoom(m_game->getId());
	}
	resp.status = SUCCEEDED;
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		this->m_handlerFactory->createMenuRequestHandler(m_user)
	};
}

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	GetQuestionResponse resp;

	try
	{
		Question q = m_handlerFactory->getGameManager()->getQuestion(*this->m_user);
		resp.answers = q.getPossibleAnswers();
		resp.question = q.getQuestion();
	}
	catch (const std::exception & e)
	{
		resp.status = FAILED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory->createMenuRequestHandler(this->m_user)
		};
	}

	resp.status = SUCCEEDED;
	return RequestResult
	{
		JsonResponsePacketSerializer::serializeResponse(resp),
		this->m_handlerFactory->createGameRequestHandler(this->m_user,this->m_handlerFactory)
	};
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	SubmitAnswerRequest req = JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(info.buffer);
	SubmitAnswerResponse resp;
	std::cout << "SUBMITTING ANSWER FROM: " << this->getUsername() << std::endl;

	resp.correctAnswerId = m_game->submitAnswer(*m_user, req.answerId,req.time);
	
	if (resp.correctAnswerId != ERROR)
	{
		resp.status = SUCCEEDED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory->createGameRequestHandler(this->m_user,this->m_handlerFactory)
		};
	}
	else
	{
		resp.status = FAILED;
		return RequestResult
		{
			JsonResponsePacketSerializer::serializeResponse(resp),
			this->m_handlerFactory->createMenuRequestHandler(this->m_user)
		};
	}
}