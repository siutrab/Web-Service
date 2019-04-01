#include "pch.h"
#include "messageSystem.h"


	messageSystem::messageSystem()
	{
	}


	messageSystem::~messageSystem()
	{
	}

	void messageSystem::handleReceivedPacket(sf::Packet* packet, Client* client)
	{
		string* messagePtr = new string;
		if (Packets::unpackMessage(packet, messagePtr))
		{
			client->setRequest(messagePtr);	//////// NO WTF
		}
		delete messagePtr;
		messagePtr = nullptr;
	}



	message::message(unsigned int numberOfPackets)
	{
		packetArray = new string[numberOfPackets];
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