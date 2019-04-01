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

bool Packets::unpackMessage(sf::Packet* packet, string* messagePointer)
{
	return (*packet >> *messagePointer);
}