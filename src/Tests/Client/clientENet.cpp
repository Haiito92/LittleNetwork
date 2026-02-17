#include <chrono>
#include <format>
#include <thread>
#include <fmt/printf.h>
#include <conio.h>
#include <iostream>
#include <LittleNetwork/Serialization/Serialization.hpp>
#include <LittleNetwork/ENet/ENetContext.hpp>
#include <enet6/enet.h>

int main(int argc, char** argv) {

    try
    {
        LN::ENetContext enetContext;

    	ENetAddress serverAddress;
    	if (enet_address_set_host(&serverAddress, ENET_ADDRESS_TYPE_ANY, "localhost") != 0)
    	{
    		std::cout << "Failed to resolve address" << std::endl;
    		return EXIT_FAILURE;
    	}
    	serverAddress.port = 10001;

		ENetHost* host = enet_host_create(serverAddress.type, nullptr, 1, 0, 0, 0);
		if (!host)
		{
			std::cerr << "Failed to create ENet host" << std::endl;
			return EXIT_FAILURE;
		}
		

		ENetPeer* peer = enet_host_connect(host, &serverAddress, 0, 0);
		{
			for (std::size_t i = 0; i < 100; ++i)
			{
				ENetEvent event;
				if (enet_host_service(host, &event, 100) > 0)
				{
					// Nous avons un événement, la connexion a soit pu s'effectuer (ENET_EVENT_TYPE_CONNECT) soit échoué (ENET_EVENT_TYPE_DISCONNECT)
					break; //< On sort de la boucle
				}
			}

			if (enet_peer_get_state(peer) != ENET_PEER_STATE_CONNECTED)
			{
				std::cout << "failed to connect" << std::endl;
				return EXIT_FAILURE;
			}

			// Si on arrive ici, on est connecté !
			std::cout << "Connected!" << std::endl;
		}

		for (;;)
		{
			std::string message;
			std::getline(std::cin, message);

		
			ENetPacket* packet = enet_packet_create(message.data(), message.size(), ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(peer, 0, packet);

			ENetEvent event;
			while (enet_host_service(host, &event, 1000) > 0)
			{
				switch (event.type)
				{
					case ENET_EVENT_TYPE_CONNECT:
					{
						std::cout << "Unexpected connect event!" << std::endl;
						break;
					}

					case ENET_EVENT_TYPE_RECEIVE:
					{
						std::cout << "Received " << event.packet->dataLength << " from client #" << event.peer->incomingPeerID << ")" << std::endl;
						std::cout << "Content: " << std::string(reinterpret_cast<const char*>(event.packet->data), event.packet->dataLength) << std::endl;

						enet_packet_destroy(event.packet);
						break;
					}

					case ENET_EVENT_TYPE_DISCONNECT:
					{
						std::cout << "Client #" << event.peer->incomingPeerID << " disconnected" << std::endl;
						break;
					}

					case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
					{
						std::cout << "Client #" << event.peer->incomingPeerID << " timed out" << std::endl;
						break;
					}

					case ENET_EVENT_TYPE_NONE:
						std::cout << "Unexpected event none" << std::endl;
						break;
					}
			}
		}
    }
    catch (std::exception& e)
    {
        throw std::runtime_error(fmt::format("Exception occured: {}\n", e.what()));
    }
    catch (...)
    {
         throw std::runtime_error(fmt::format("Unknown exception occured\n"));
    }
}
