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
	this->h.sendData(s, HELLO_MSG);
	
	// Receive hello message from the client.
	this->h.getPartFromSocket(s,MSG_LEN);

	do
	{

	} while (true);
	/*SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(this->h.getAllTheSocket(s));
	SignupResponse response{ 1 };

	Buffer binResponse = JsonResponsePacketSerializer::serializeResponse(response);
	std::string headers(1, static_cast<unsigned char>(binResponse.code));
	// Get the sign up request from the client.
	SignupRequest request= JsonRequestPacketDeserializer::deserializeSignupRequest(this->h.getAllTheSocket(s));

	// Create the sign up response.
	SignupResponse response;
	response.status = 1;
	Buffer binResponse  =JsonResponsePacketSerializer::serializeResponse(response);

	// Send the sign up response to the client.
	std::string headers(1,static_cast<unsigned char>(binResponse.code));

	headers += reinterpret_cast<char const*>(binResponse.dataLen);
	std::string data (binResponse.data.begin(), binResponse.data.end());
	this->h.sendData(s,headers+data);

	while (!this->m_isEnded)
	{
		// Get the login request from the client.
		LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(this->h.getAllTheSocket(s));

		// Create the login response.
		LoginResponse response;
		response.status = 1;
		Buffer binResponse = JsonResponsePacketSerializer::serializeResponse(response);

		// Send the login response to the client.
		std::string headers(1, static_cast<unsigned char>(binResponse.code));
		headers += reinterpret_cast<char const*>(binResponse.dataLen);
		std::string data(binResponse.data.begin(), binResponse.data.end());
		this->h.sendData(s, headers + data);
	}*/


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

		// Adding the client to the clients map.
		LoginRequestHandler handler = LoginRequestHandler();
		std::pair<SOCKET, IRequestHandler*> client(clientSocket, &handler);
		m_clients.insert(client);

		// Creating a detached thread that handles the new client.
		std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
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