#include "pch.h"
#include "server.h"

///
// SERVER
///

	server::server(size_t port)
		: port(port)
	{
		msgSystem = new messageSystem(this);
		connectedClients = new ConnectedClients(this);
		listener.setBlocking(false);
	}

	server::~server()
	{

		// Deleting pointers
		delete connectedClients;
		connectedClients = nullptr;
			
		delete msgSystem;
		msgSystem = nullptr;

	}

	/// Initializes the server and starts its main loop
	void server::start()
	{
		listener.listen(port);
		selector.add(listener);	// adding first listener socket
		running = true;			// initializing server
		while (running)
		{
			if (selector.wait())	// waits for data at any socket, at listener as well
			{
				lookForNewClients();
				connectedClients->listen();
			}
		}
	}

	void server::stop() { running = false; }

	///	Checks if there are more clients that want to connect
	void server::lookForNewClients()
	{
		// if socket is not occupied
		if (selector.isReady(listener))		
		{
			sf::TcpSocket* socket = new sf::TcpSocket();
			socket->setBlocking(false);

			// accepting new socket
			if (listener.accept(*socket) == sf::Socket::Done)
			{
				connectedClients->addClient(socket);
				selector.add(*socket);
			}
			else delete socket;
		}
	}

	/// Receiving message and saves it in string receivedMessage
	/// returns true if succeed
	bool server::receiveMessage(Client* client)
	{
		sf::TcpSocket* socket = (client->getSocket());

		if(selector.isReady(*socket))
		{
			sf::Packet* packet = new sf::Packet();

			if (socket->receive(*packet) == sf::Socket::Done)
			{
				msgSystem->handleReceivedPacket(packet, client);
				return true;
			}
			delete packet;
		}
		return false;
	}

///
// CONNECTED CLIENTS
///

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

		void ConnectedClients::clearList()
		{
			// Deleting heap
			for (std::list<Client*>::iterator i = ClientsList.begin(); i != ClientsList.end(); i++)
			{
				Client* client = *i;
				delete client;
			}

			// Deleting pointers
			ClientsList.clear();
		}

		void ConnectedClients::addClient(sf::TcpSocket* socket)
		{
			Client* client = new Client(socket);
			ClientsList.push_back(client);
			numberOfClients++;
		}

		void ConnectedClients::removeClient(Client* client)
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


		ConnectedClients* server::getConnectedClients() { return connectedClients; }

///
// CLIENT
///

Client::Client(sf::TcpSocket* socket)
	:	socket(socket),
		request(new message()),
		response(new message())
{
			
}

Client::~Client()
{
	delete socket;
	socket = nullptr;
}

sf::TcpSocket* Client::getSocket() { return socket; }
message* Client::getRequest() { return request; }
void Client::setRequest(packetStructure* packet) { request->insertPacket(packet); }
void Client::setResponse(string* message) { response->insertPacket(message); }