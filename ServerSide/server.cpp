#include "pch.h"
#include "server.h"


server::server(size_t port)
	: port(port)
{

}


server::~server()
{
}

///
// METHODS
///

/// Waits until a client connect, and returns his ip address when it happens
sf::IpAddress server::listen()
{
	sf::Packet packet;

	listener.listen(port);
	listener.accept(socket);	// Waiting for connection

	socket.receive(packet);

	Packets::unpackMessage(packet, receivedMessage);


	cout << "The client said: " << * receivedMessage << endl;
	cout << socket.getRemoteAddress() << endl;
	return socket.getRemoteAddress();
}
