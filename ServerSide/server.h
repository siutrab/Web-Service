#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Packets.h"
#include <list>
#include <iterator>
#include <memory>
#include "messageSystem.h"


class ConnectedClients;
class Client;
class server;
class messageSystem;
class message;

using namespace std;
class server
{
private:
	bool running;
	messageSystem* msgSystem;
	sf::TcpSocket socket;
	sf::TcpListener listener;
	sf::SocketSelector selector;
	size_t port;
	ConnectedClients* connectedClients;

	void lookForNewClients();	
public:
	server(size_t port);
	~server();
	void start();
	void stop();
	bool receiveMessage(Client* client);
};


class ConnectedClients
{
private:
	list<Client*> ClientsList;
	server* serverPointer;
	unsigned int numberOfClients;

	void clearList();	// For destructor purposes
public:
	ConnectedClients(server * serverPtr);
	~ConnectedClients();
	void addClient(sf::TcpSocket* socket);
	void removeClient(Client* client);
	void listen();
};

class Client
{
	friend class ConnectedClients;

private:
	sf::TcpSocket* socket;
	message* request;
	message* response;

public:
	Client(sf::TcpSocket* socket);
	~Client();
	inline sf::TcpSocket* getSocket();
	inline void setRequest(string* message);
	inline void setResponse(string* message);
	inline message* getRequest();
};



