#pragma once
#include "SFML/Network.hpp"
#include <iostream>

using namespace std;
class Packets
{
	Packets();
	~Packets();
public:

	static bool packMessage(const string & message, sf::Packet & packet);
	static bool unpackMessage(sf::Packet & packet, string* messagePointer);
};

