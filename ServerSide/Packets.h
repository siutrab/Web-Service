#pragma once
#include "SFML/Network.hpp"
#include <iostream>

using namespace std;
class Packets
{
	Packets();
	~Packets();
public:

	static bool packMessage(sf::Packet* packet, string* message);
	static bool unpackMessage(sf::Packet* packet, string* messagePointer);
};

