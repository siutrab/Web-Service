#include "pch.h"
#include "client.h"


///
// CLIENT CLASS
///

		client::client()
		{
		}


		client::~client()
		{
			delete receivedMessage;
			receivedMessage = nullptr;

			delete givenMessage;
			givenMessage = nullptr;
		}

	// Methods
		bool client::sendMessage(const string & message)
		{
			// if connection failed
			if (socket.connect(*(ServerInfo::getIp()), ServerInfo::getPort(), maxConnectionTime) != sf::Socket::Done)
			{
				return false;
			}

			sf::Packet packet;

			sf::Int64 length = 10;
			sf::Int64 index = 0;
			sf::Int64 maxIndex = 5;
			string content = message;

			if (packet << length << index << maxIndex << content)
			{
				socket.send(packet);
				return true;
			}
			return false;
		}

		bool client::receiveMessage()
		{
			sf::Packet* packet = new sf::Packet();
			socket.receive(*packet);
			//return Packets::unpackMessage(packet, receivedMessage);
			return true;
		}
		


///
// SERVER INFO
///

	// Fields
		size_t ServerInfo::port = 54000;
		sf::IpAddress ServerInfo::ip = sf::IpAddress::getLocalAddress();

	// Getters
		size_t ServerInfo::getPort()
		{
			return ServerInfo::port;
		}
		sf::IpAddress* ServerInfo::getIp()
		{
			return & ServerInfo::ip;
		}
	// Setters
		void ServerInfo::setPort(size_t port)
		{
			ServerInfo::port = port;
		}
		void ServerInfo::setIp(sf::IpAddress* ip)
		{
			ServerInfo::ip = *ip;
		}

	// Methods

