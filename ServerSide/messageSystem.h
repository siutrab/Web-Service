#pragma once
#include "SFML/Network.hpp"
#include "server.h"
#include "Packets.h"

using namespace std;
class message;
class Client;
class ConnectedClients;
class Packet;
struct packetStructure;
class server;

class messageSystem
{
	server* parentServer;
	ConnectedClients* clientsPtr;
public:
	messageSystem(server* parentServer);
	~messageSystem();

	void handleReceivedPacket(sf::Packet* packet, Client* client);
};

class message
{
private:
	sf::TcpSocket socket;
	string* consolidatedMessage;
	string* packetArray;

	bool empty = true;		// If there are no packets there

	unsigned int numberOfPackets = 1;
	unsigned int actualPacketIndex;		// starts from 0 index
public:

	message(unsigned int numberOfPackets = 1);
	~message();
	void insertPacket(string* packet);	// inserts a packet in a specific index of a message
	void insertPacket(packetStructure* packet);
	bool convertToPackets(sf::Packet* packetArray);
	bool consolidateString();
};

