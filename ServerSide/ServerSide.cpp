﻿#include "pch.h"
#include <iostream>
#include "SFML/Network.hpp"	
#include "server.h"


int main()
{
	server* serverPointer = new server(54000);
	serverPointer->listen();
	int a;
	cin >> a;
}
