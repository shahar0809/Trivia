#include "Communicator.h"
#define HELLO_MSG "Hello"
#define MSG_LEN 5
#define PORT 1050
#define _CRT_SECURE_NO_WARNINGS
std::mutex isEnded;

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
	//std::pair<std::string, int> socketInfo;
	//sa.sin_port = htons(socketInfo.second);  //didn't work to me, maybe something is missing 

	sa.sin_port = htons(PORT); // Port that server will listen to
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

void Communicator::handleNewClient(SOCKET s)
{
	//Should short it, there is no need in 2 variables.
	const char* data = HELLO_MSG;

	//Send hello message
	std::cout << strlen(data);
	if (send(s, data, strlen(data), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
	
	//Recieve hello message.
	char* dataRecieved = new char[MSG_LEN+1];
	int res = recv(s, dataRecieved, MSG_LEN, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(this->m_clients.begin()->first);
		throw std::exception(s.c_str());
	}
	dataRecieved[MSG_LEN] = 0;
	std::cout << dataRecieved << std::endl;

	while (!this->_isEnded)
	{
		//Do something... will be added in the next versions.
	}
	closesocket(s);
}

void Communicator::startHandleRequests()
{
	SOCKET listeningSocket = bindAndListen();

	// Listening for new clients and accepting them.
	while (!this->_isEnded) 
	{
		// Accepting the client and creating a specific socket from the server to this client.
		SOCKET clientSocket = ::accept(listeningSocket, NULL, NULL);

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
	//Update the variable so all the threads will know to stop.
	std::unique_lock <std::mutex> locker(isEnded);
	this->_isEnded = _isEnded;
	locker.unlock();
}