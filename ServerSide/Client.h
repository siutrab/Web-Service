#pragma once
#include "server.h"
#include "SFML/Network.hpp"	

class Client
{
	friend class ConnectedClients;

private:
	sf::IpAddress ip;
	size_t port;
	sf::TcpSocket* socket;
public:
	Client(sf::TcpSocket* socket);
	~Client();
	inline sf::TcpSocket* getSocket();
};

