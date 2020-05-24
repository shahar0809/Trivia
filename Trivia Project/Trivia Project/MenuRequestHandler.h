#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	~MenuRequestHandler();

	virtual bool isRequestRelevant(RequestInfo);
	virtual RequestResult handleRequest(RequestInfo);
};

