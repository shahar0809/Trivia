#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(LoggedUser* user, GameManager* gameManager, RequestHandlerFactory* handlerFactory)
{
	this->m_gameManager = *gameManager;
	this->m_handlerFactory = *handlerFactory;
	this->m_user = user;
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

}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{

}

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{

}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{

}