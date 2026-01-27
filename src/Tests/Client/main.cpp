#include <chrono>
#include <format>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <fmt/printf.h>
#include <LittleNetwork/WSAContext.hpp>
#include <LittleNetwork/ClientTCPSocket.hpp>
#include <conio.h>
#include <iostream>

int main(int argc, char** argv) {

    try
    {
        Ln::WSAContext wsaContext;

        Ln::ClientTCPSocket clientSocket;
        
        sockaddr_in serverIp;
        serverIp.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &serverIp.sin_addr);
        serverIp.sin_port = htons(10001);
        
        clientSocket.Connect(serverIp);

        std::string message;
        std::cout << "> ";
        bool isRunning = true;
        while (isRunning)
        {
            if (_kbhit()) //< Est-ce qu'une touche est enfoncée ?
            {
                char c = _getch(); //< On récupère la touche enfoncée (sans l'afficher)
                if (c == '\b') //< gestion du retour arrière
                {
                    if (!message.empty())
                    {
                        // Afficher un retour arrière déplace juste le curseur vers le caractère précédent
                        // pour l'effacer nous pouvons mettre un espace et redéplacer le curseur à nouveau vers l'arrière
                        std::cout << "\b \b";

                        // On enlève le caractère de notre message en cours
                        message.pop_back();
                    }
                }

                else if (c == '\r')
                {
                    // \r correspond à l'appui sur la touche entrée, on envoie le message si celui-ci n'est pas vide
                    if (message.empty())
                    {
                        isRunning = false;
                        break; //< message vide, on casse la boucle
                    }

                    // Gestion et/ou envoi du message au serveur
                    clientSocket.Send(message);

                    // On affiche un retour à la ligne et le marqueur de saisie
                    std::cout << "\n> " << std::flush;

                    // On vide le message pour revenir à la suite
                    message.clear();
                }
                else
                {
                    std::cout << c; // on affiche le caractère
                    message.push_back(c); // on rajoute tout autre caractère dans notre saisie
                }
            }

            // Gestion de la réception des info de la part du serveur

            std::vector<WSAPOLLFD> descriptors;
            {
                WSAPOLLFD descriptor;
                descriptor.fd = clientSocket.GetHandle();
                descriptor.events = POLLIN;
                descriptor.revents = 0;
                descriptors.push_back(descriptor);
            }
            
            // Ask why timeout == -1
            int activeSocketCount = WSAPoll(descriptors.data(), descriptors.size(), 0);
            
            if (activeSocketCount == SOCKET_ERROR)
            {
                throw std::runtime_error(fmt::format("Error when polling: {}\n", WSAGetLastError()));
            }
            
            if (activeSocketCount == 0)
            {
                continue;
            }
            
            for (WSAPOLLFD& descriptor : descriptors)
            {
                if (descriptor.revents == 0)
                    continue;
            
                if (descriptor.fd == clientSocket.GetHandle())
                {
                    char buffer[1024];
                    int byteRead = recv(descriptor.fd, buffer, sizeof(buffer), 0);
                    if (byteRead == 0 || byteRead == SOCKET_ERROR)
                    {
                        if (byteRead == SOCKET_ERROR)
                            fmt::print("Failed to read from server ({})\n", WSAGetLastError());
					       
                        continue;
                    }
            
                    fmt::print("{}", std::string_view(buffer, byteRead));
                    std::cout << "\n> " << std::flush;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        fmt::print("Catched standard exception: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("Catched unknown exception\n");
    }

    return 0;
}
