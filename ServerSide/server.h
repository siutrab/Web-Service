#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Packets.h"


using namespace std;
class server
{
private:
	string* receivedMessage;
	string* givenMessage;

	sf::TcpSocket socket;
	sf::TcpListener listener;
	size_t port;
	
public:
	server(size_t port);
	~server();
	sf::IpAddress listen();
};

class ClientInfo
{
public:
	sf::IpAddress ip;
	size_t port;

};



