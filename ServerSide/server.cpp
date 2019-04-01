#include "pch.h"
#include "server.h"

///
// SERVER
///

		server::server(size_t port)
			: port(port)
		{
			msgSystem = new messageSystem();
			connectedClients = new ConnectedClients(this);
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

		void server::stop()
		{
			running = false;
		}

		///	Checks if there are more clients that want to connect
		void server::lookForNewClients()
		{
			// if socket is not occupied
			if (selector.isReady(listener))		
			{
				sf::TcpSocket* socket = new sf::TcpSocket();

				// accepting new socket
				if (listener.accept(*socket) == sf::Socket::Done)
				{
					connectedClients->addClient(socket);
					selector.add(*socket);
				}
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


		/*
		///// Waits until a client connect, and returns his ip address when it happens
		//void server::listen()
		//{
		//	//sf::Packet packet;

		//	//listener.listen(port);
		//	//listener.accept(socket);	// Waiting for connection

		//	//socket.receive(packet);		// Receiving package

		//	//Packets::unpackMessage(packet, receivedMessage);
		//	//
		//	//cout << "The client said: " << * receivedMessage << endl;
		//	//cout << socket.getRemoteAddress() << endl;
		//	//return socket.getRemoteAddress();
		//	
		//	//////for (std::list<Client*>::iterator i = connectedClients->ClientsList.begin(); i != connectedClients->ClientsList.end(); i++)
		//	//////{
		//	//////	Client* client = *i;
		//	//////	sf::TcpSocket* clientsSocket = client->socket;
		//	//////}

		//}
		*/


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


///
// CLIENT
///

		Client::Client(sf::TcpSocket* socket)
			: socket(socket)
		{

		}

		Client::~Client()
		{
			delete socket;
			socket = nullptr;
		}

		sf::TcpSocket* Client::getSocket() { return socket; }
		message* Client::getRequest() { return request; }
		inline void Client::setRequest(string* message) { request->insertPacket(message); }
		inline void Client::setResponse(string* message) { response->insertPacket(message); }