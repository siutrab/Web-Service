#include "pch.h"
#include "Packets.h"


Packets::Packets()
{
}


Packets::~Packets()
{
}

bool Packets::packMessage(sf::Packet* packet, string* message)
{
	 return (*packet << *message);
}

//bool Packets::unpackMessage(sf::Packet* packet, string* messagePointer)
//{
//	return (*packet >> *messagePointer);
//}

packetStructure* Packets::unpackMessage(sf::Packet* packet)
{
	sf::Int64 length, index, maxIndex;
	string content;
	packetStructure* packetStruct = new packetStructure;
	if (*packet >> packetStruct->length >> packetStruct->index >> packetStruct->maxIndex >> packetStruct->content)
	{
		packetStruct->succeed = true;
	}
	return packetStruct;
}