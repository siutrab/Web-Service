#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Packets.h"


using namespace std;

class client
{
private:
	sf::Time maxConnectionTime;
	sf::TcpSocket socket;
	sf::IpAddress ip;
	size_t port;
	string* receivedMessage = new string;
	string* givenMessage = new string;

public:
	client();
	~client();
	bool sendMessage(const string & message);
	bool receiveMessage();
};


class ServerInfo
{
private:
	static size_t port;
	static sf::IpAddress ip;

	ServerInfo();
	~ServerInfo();
public:

	static size_t getPort();
	static sf::IpAddress* getIp();

	static void setPort(size_t port);
	static void setIp(sf::IpAddress* ip);
};
