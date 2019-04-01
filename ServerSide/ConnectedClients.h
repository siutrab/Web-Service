#pragma once
#include "server.h"
#include "Client.h"
class ConnectedClients
{
private:
	server* serverPointer;
	unsigned int numberOfClients;

	list<Client*> ClientsList;

	void clearList();	// For destructor purposes
public:

	ConnectedClients(server * serverPtr);
	~ConnectedClients();

	// Methods
	void addClient(sf::TcpSocket* socket);
	bool removeClient(Client* client);
	void listen();

};

