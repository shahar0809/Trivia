#include "Server.h"

void Server::run()
{
	// Creating the database, and the handler factory.
	this->m_database = new SqliteDatabase();
	this->m_handlerFactory = RequestHandlerFactory(this->m_database);

	this->m_communicator = Communicator(m_database);
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
	std::cout.flush();
	std::cout << " *** Starting Trivia : Server Side ... ***" << std::endl;
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