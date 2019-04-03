#pragma once
#include "SFML/Network.hpp"
#include <iostream>
struct packetStructure;
using namespace std;
class Packets
{
	Packets();
	~Packets();
public:

	static bool packMessage(sf::Packet* packet, string* message);
	static bool unpackMessage(sf::Packet* packet, string* messagePointer);
	static packetStructure* unpackMessage(sf::Packet* packet);
};

struct packetStructure
{
	sf::Int64 length;
	sf::Int64 index;
	sf::Int64 maxIndex;
	string content;
	bool succeed = false;
};