#pragma once
#include "Game.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser* user, GameManager* gameManager, RequestHandlerFactory* handlerFactory);

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

private:
	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);

	// Class members
	Game m_game;
	LoggedUser* m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
};

