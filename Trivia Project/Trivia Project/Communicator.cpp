#include "Communicator.h"

SOCKET Communicator::bindAndListen()
{
	// Creating the listening socket of the server.
	SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Checking that it's valid.
	if (listeningSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

	/* Initializing socket. */
	struct sockaddr_in sa = { 0 };
	std::pair<std::string, int> socketInfo;
	sa.sin_port = htons(socketInfo.second);  // Port that server will listen to
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;     

	// Connects between the socket and the configuration (port and etc..)
	if (bind(listeningSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	return listeningSocket;
}

void Communicator::handleNewClient()
{

}

void Communicator::startHandleRequests()
{
	SOCKET listeningSocket = bindAndListen();

	// Listening for new clients and accepting them.
	while (true)
	{
		// Accepting the client and creating a specific socket from the server to this client.
		SOCKET clientSocket = ::accept(listeningSocket, NULL, NULL);

		if (clientSocket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		// Creating a detached thread that handles the new client.
		std::thread clientThread(&Communicator::handleNewClient, this);
		clientThread.detach();

		// Adding the client to the clients map.
		LoginRequestHandler handler = LoginRequestHandler();
		std::pair<SOCKET, IRequestHandler*> client(clientSocket, &handler);
		m_clients.insert(client);
	}
}
