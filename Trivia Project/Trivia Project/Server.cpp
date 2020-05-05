#include "Server.h"
#define EXIT_REQUEST "EXIT"

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
	Server s;
	s.run();
}