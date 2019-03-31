#include "pch.h"
#include "Packets.h"


Packets::Packets()
{
}


Packets::~Packets()
{
}

bool Packets::packMessage(const string & message, sf::Packet & packet)
{
	 return (packet << message);
}

bool Packets::unpackMessage(sf::Packet & packet, string* messagePointer)
{
	return (packet >> *messagePointer);
}