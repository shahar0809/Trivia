#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequesHandler()
{
	LoginRequestHandler loginReq = LoginRequestHandler();
	return &loginReq;
}

// LoginManager getter
LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}
