/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:26:28 by ataouaf           #+#    #+#             */
/*   Updated: 2024/01/09 05:28:38 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
# include <sys/types.h>
# include <sys/time.h>


# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define BUFFER_SIZE 1024

class Client;


class Server
{
    private:
        std::string _server_name; // server_name is a string of 32 characters
        std::string _password; // password is a string of 8 characters
        std::string _start_time; // start_time is a string of 32 characters
        int _port; // port is a 16-bit unsigned integer
        int _socket; // socket is an endpoint for communication
        struct sockaddr_in _client_address; // sockaddr_in is a structure containing an internet address (IPv4)
        struct pollfd *_fds;
        std::vector<Client *> _users;
        // std::vector<Channel *> _chanels; // channels is a list of channels
    public:
        Server();
        Server(std::string password, int port);
        ~Server();

        std::string dateString();
        void run();
        void setNonBlocking(int fd);
        void constructDescriptorSet();
        void acceptNewConnection();
        void addNewClient(int fd, std::string ip, int port);
        void readFromClient(Client *client);
        void removeClient(int fd);
        void handleCommands(Client *client, std::string &command);
        
};

# endif