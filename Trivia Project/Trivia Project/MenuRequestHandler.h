#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	~MenuRequestHandler();

	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
};

