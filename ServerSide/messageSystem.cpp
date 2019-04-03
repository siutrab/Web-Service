#include "pch.h"
#include "messageSystem.h"


messageSystem::messageSystem(server* parentServer)
	:	parentServer(parentServer), 
		clientsPtr(parentServer->getConnectedClients())
{
}


messageSystem::~messageSystem()
{
}

void messageSystem::handleReceivedPacket(sf::Packet* packet, Client* client)
{
	packetStructure* unpackMsg = Packets::unpackMessage(packet);
	if (unpackMsg->succeed)
	{
		client->setRequest(unpackMsg);
	}
	else delete unpackMsg;
}



message::message(unsigned int numberOfPackets)
{
}
message::~message()
{
	delete[] packetArray;
}

void message::insertPacket(string* packet)
{
	packetArray[actualPacketIndex] = *packet;
	actualPacketIndex++;
}

void message::insertPacket(packetStructure* packet)
{
	if(empty)
	{
		packetArray = new string[packet->maxIndex];		// Array length is number of packets in whole message
	}
	packetArray[packet->index] = packet->content;
	empty = false;

	// packet is unpacked so it can be removed
	delete packet;
	packet = nullptr;
}