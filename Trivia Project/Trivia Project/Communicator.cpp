#include "Communicator.h"

#define _CRT_SECURE_NO_WARNINGS
std::mutex isEnded;

void Communicator::bindAndListen()
{
	// Creating the listening socket of the server.
	m_listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Checking that the socket is valid.
	if (m_listeningSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

	/* Initializing socket. */
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT); // Port that server will listen to
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;     

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_listeningSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(m_listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
}

void Communicator::handleNewClient(std::pair<SOCKET, IRequestHandler*> client)
{
	// Send hello message to the client.
	Helper::sendData(client.first, HELLO_MSG);
	
	// Receive hello message from the client.
	Helper::getPartFromSocket(client.first, MSG_LEN);

	do
	{
		std::string packet = Helper::getAllTheSocket(client.first);
		RequestInfo info(packet);  //
		
		if (!client.second->isRequestRelevant(info))
		{
			ErrorResponse errResponse{ "Request is not relevant." };
			Helper::sendData(client.first, JsonResponsePacketSerializer::serializeResponse(errResponse));
		}
		RequestResult result = client.second->handleRequest(info);
		Helper::sendData(client.first, result.requestBuffer);
	} while (!this->m_isEnded);
	closesocket(client.first);
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	// Listening for new clients and accepting them.
	while (!this->m_isEnded) 
	{
		// Accepting the client and creating a specific socket from the server to this client.
		SOCKET clientSocket = ::accept(m_listeningSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		// Adding the client to the clients map.
		LoginRequestHandler handler = LoginRequestHandler();
		std::pair<SOCKET, IRequestHandler*> client(clientSocket, &handler);
		m_clients.insert(client);

		// Creating a detached thread that handles the new client.
		std::thread clientThread(&Communicator::handleNewClient, this, client);
		clientThread.detach();
	}
}

void Communicator::setIsEnded(bool _isEnded)
{
	// Update the variable so all the threads will know to stop executing.
	std::unique_lock <std::mutex> locker(isEnded);
	this->m_isEnded = _isEnded;
	locker.unlock();
}