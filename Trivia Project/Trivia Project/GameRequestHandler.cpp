#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(LoggedUser* user, GameManager* gameManager, RequestHandlerFactory* handlerFactory)
{
	this->m_gameManager = gameManager;
	this->m_handlerFactory = handlerFactory;
	this->m_user = user;
	this->m_game = this->m_gameManager->getGame(*user);
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
	if (m_handlerFactory->getGameManager()->deleteGame(*this->m_user))
	{
		resp.status = SUCCEEDED;
	}
	else
	{
		resp.status = FAILED;
	}

	return RequestResult
	{
		JsonResponsePacketSerializer::serializeLeaveGameResponse(resp),
		this->m_handlerFactory->createMenuRequestHandler(this->m_user)
	};
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult f;
	return f;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	RequestResult f;
	return f;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult f;
	return f;
}