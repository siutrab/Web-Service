#include "pch.h"
#include "Client.h"


Client::Client(sf::TcpSocket* socket)
	: socket(socket)
{

}

Client::~Client()
{
	delete socket;
	socket = nullptr;
}

inline sf::TcpSocket* Client::getSocket() { return socket; }
