#include "Server.h"

void Server::run()
{
	this->m_communicator = Communicator();
	std::thread t_connector(&Communicator::startHandleRequests, this->m_communicator);
	t_connector.detach();

	std::string consoleInput;
	while (consoleInput != EXIT_REQUEST)
	{
		std::cin >> consoleInput;
	}
	this->m_communicator.setIsEnded(true);
}

void main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;
		myServer.run();
	}
	catch (std::exception & e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}