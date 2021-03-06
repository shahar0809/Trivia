#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* handler) 
{
	this->m_handlerFactory = *handler;
	m_loginManager = m_handlerFactory.getLoginManger();
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.requestId == LOGIN_CODE || info.requestId == SIGN_UP_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	if (info.requestId == LOGIN_CODE)
	{
		return login(info);
	}
	else if (info.requestId == SIGN_UP_CODE)
	{
		return signup(info);
	}
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
	LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
	LoginResponse response;
	RequestResult result;
	LoggedUser* user = m_loginManager->login(loginReq.username, loginReq.password);
	

	if (user != nullptr)
	{
		this->m_username = user->getUsername();
		response.status = SUCCEEDED;
		result.newHandler = m_handlerFactory.createMenuRequestHandler(user); // Setting next state to the menu handler.
	}
	else
	{
		response.status = FAILED;
		result.newHandler = m_handlerFactory.createLoginRequestHandler();// Setting next state to the login handler again.
	}
	result.requestBuffer = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
	SignupResponse response;
	RequestResult result;

	if (m_loginManager->signup(signupReq.username, signupReq.password, signupReq.email))
	{
		response.status = 1;
		result.newHandler = m_handlerFactory.createLoginRequestHandler(); // Setting next state to the login handler.
	}
	else
	{
		response.status = 0;
		result.newHandler = m_handlerFactory.createLoginRequestHandler();// Setting next state to the login handler again.
	}
	result.requestBuffer = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

