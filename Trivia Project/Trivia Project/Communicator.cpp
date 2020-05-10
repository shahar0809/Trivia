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

void Communicator::handleNewClient(SOCKET s)
{
	// Send hello message to the client.
	if (send(s, HELLO_MSG, strlen(HELLO_MSG), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
	
	// Receive hello message from the client.
	char* dataRecieved = new char[MSG_LEN + 1];
	int result = recv(s, dataRecieved, MSG_LEN, 0);

	if (result == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(this->m_clients.begin()->first);
		throw std::exception(s.c_str());
	}
	dataRecieved[MSG_LEN] = 0;
	std::cout << dataRecieved << std::endl;
	delete[] dataRecieved;

	while (!this->m_isEnded)
	{
		// Do something... will be added in the next versions.
	}
	closesocket(s);
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

		// Creating a detached thread that handles the new client.
		std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
		clientThread.detach();

		// Adding the client to the clients map.
		LoginRequestHandler handler = LoginRequestHandler();
		std::pair<SOCKET, IRequestHandler*> client(clientSocket, &handler);
		m_clients.insert(client);
	}
}

void Communicator::setIsEnded(bool _isEnded)
{
	// Update the variable so all the threads will know to stop executing.
	std::unique_lock <std::mutex> locker(isEnded);
	this->m_isEnded = _isEnded;
	locker.unlock();
}