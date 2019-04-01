#pragma once
#include "SFML/Network.hpp"
#include "server.h"
#include "Packets.h"

using namespace std;
class message;
class Client;
class ConnectedClients;
class Packet;

class messageSystem
{

public:
	messageSystem();
	~messageSystem();

	void handleReceivedPacket(sf::Packet* packet, Client* client);
};

class message
{
private:
	sf::TcpSocket socket;
	string* consolidatedMessage;
	string* packetArray;

	unsigned int numberOfPackets;
	unsigned int actualPacketIndex;		// starts from 0 index
public:

	message(unsigned int numberOfPackets);
	~message();
	void insertPacket(string* packet);	// inserts a packet in a specific index of a message
	bool convertToPackets(sf::Packet* packetArray);
	bool consolidateString();
};

