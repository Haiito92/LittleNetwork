#include <format>
#include <iostream>
#include <thread>
#include <fmt/printf.h>
#include <vector>
#include <LittleNetwork/Serialization/Serialization.hpp>
#include <LittleNetwork/ENet/ENetContext.hpp>
#include <enet6/enet.h>


int main(int argc, char** argv) {

    try
    {
        LN::ENetContext enetContext;

    	ENetAddress address;
    	enet_address_build_any(&address, ENET_ADDRESS_TYPE_IPV6);
    	address.port = 10001;

		ENetHost* host = enet_host_create(ENET_ADDRESS_TYPE_ANY, &address, 10, 0, 0, 0);
		if (!host)
		{
			std::cerr << "Failed to create ENet host" << std::endl;
			return EXIT_FAILURE;
		}

		for (;;)
		{
			ENetEvent event;
			while (enet_host_service(host, &event, 1000) > 0)
			{
				switch (event.type)
				{
					case ENET_EVENT_TYPE_CONNECT:
					{
						char address[128];
						enet_address_get_host(&event.peer->address, address, 128);

						std::cout << "A new client (#" << event.peer->incomingPeerID << ") connected from " << std::string(address) << std::endl;
						break;
					}

					case ENET_EVENT_TYPE_RECEIVE:
					{
						std::cout << "Received " << event.packet->dataLength << " from client #" << event.peer->incomingPeerID << ")" << std::endl;
						std::cout << "Content: " << std::string(reinterpret_cast<const char*>(event.packet->data), event.packet->dataLength) << std::endl;

						enet_peer_send(event.peer, 0, event.packet);
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
