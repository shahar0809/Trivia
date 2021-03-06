#include "Communicator.h"

#define _CRT_SECURE_NO_WARNINGS
std::mutex isEnded;

Communicator::Communicator(IDatabase* db) : m_isEnded(false)
{
	this->m_handlerFactory = *new RequestHandlerFactory(db);
}

/**
* Binds the socket and the configuration, starts listening for incoming requests.
* return: None.
*/
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

/**
* Handles a new client after a socket was created.
* @param client: contains the connecting socket, and the current request handler.
* return: None.
*/
void Communicator::handleNewClient(std::pair<SOCKET, IRequestHandler*> client)
{
	//IRequestHandler* currHandler = client.second;
	std::string username;

	/* Getting requests from the client */
	while (!this->m_isEnded)
	{
		/* Getting the packet from the socket. */
		std::string packet;
		try
		{
			packet = Helper::getAllTheSocket(client.first);
		}
		catch (const std::exception & e)
		{
			closesocket(client.first);
			this->m_clients.erase(client.first);
			m_handlerFactory.getLoginManger()->logout(client.second->getUsername());
			return; // End thread execution
		}
		
		RequestInfo info(packet);  // Analyzing the packet
		std::cout << "C L I E N T\n" << packet << std::endl;
		if (!client.second->isRequestRelevant(info))
		{
			ErrorResponse errResponse{ "Request is not relevant." };
			Helper::sendData(client.first, JsonResponsePacketSerializer::serializeResponse(errResponse));
		}
		else
		{
			RequestResult result = client.second->handleRequest(info);  // Passing the request to the handler.
			std::cout << "S E R V E R:" << std::endl << result.requestBuffer << std::endl << std::endl;
			Helper::sendData(client.first, result.requestBuffer);       // Sending response to the client

			client.second = result.newHandler; // Moving to the next state (updating handler).
		}
	} 
	closesocket(client.first);
	this->m_clients.erase(client.first);
	m_handlerFactory.getLoginManger()->logout(client.second->getUsername());
}

/**
* Accepts incoming requests (if valid), and creates a new socket and a thread that handle the client.
* return: None.
*/
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
		std::pair<SOCKET, IRequestHandler*> client(clientSocket, m_handlerFactory.createLoginRequestHandler());
		m_clients.insert(client);

		// Creating a detached thread that handles the new client.
		std::thread clientThread(&Communicator::handleNewClient, this, client);
		clientThread.detach();
	}
}

/**
* Closes all threads.
* return: none.
*/
void Communicator::setIsEnded(bool _isEnded)
{
	// Update the variable so all the threads will know to stop executing.
	std::unique_lock <std::mutex> locker(isEnded);
	this->m_isEnded = _isEnded;
	locker.unlock();
}