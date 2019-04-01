#include "pch.h"
#include "ConnectedClients.h"


ConnectedClients::ConnectedClients(server * serverPtr)
	: serverPointer(serverPtr)
{

}

ConnectedClients::~ConnectedClients()
{
	serverPointer = nullptr;
	// Deleting list
	clearList();
}

// Methods
void ConnectedClients::clearList()
{
	for (std::list<Client*>::iterator i = ClientsList.begin(); i != ClientsList.end(); i++)
	{
		Client* client = *i;
		delete client;
	}
}

void ConnectedClients::addClient(sf::TcpSocket* socket)
{
	Client* client = new Client(socket);
	ClientsList.push_back(client);
	numberOfClients++;
}

bool ConnectedClients::removeClient(Client* client)
{
	ClientsList.remove(client);
}

void ConnectedClients::listen()
{
	for (std::list<Client*>::iterator i = ClientsList.begin(); i != ClientsList.end(); i++)
	{
		Client* client = *i;
		serverPointer->receiveMessage(client);
	}
}

