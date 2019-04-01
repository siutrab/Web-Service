#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ServerSide/server.h"
#include "SFML/Network.hpp"	

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(ServerSide_server)
	{
	public:
		
		TEST_METHOD(ServerConnection)
		{
			string message = "message";
			sf::TcpSocket socket;
			sf::IpAddress ip = sf::IpAddress::getLocalAddress();
			unsigned int port = 54000;
			socket.connect(ip, port);
			sf::Packet packet;
			packet << message;
			server servTest(port);
			servTest.start();
			socket.send(packet);

			
		}

	};
}