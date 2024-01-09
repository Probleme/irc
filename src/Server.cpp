/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:26:16 by ataouaf           #+#    #+#             */
/*   Updated: 2024/01/09 02:48:58 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"
#include "../inc/Client.hpp"

Server::Server()
{
}

Server::Server(std::string password ,int port) : _server_name("Problem_irc"),_password(password), _start_time(dateString()), _port(port),  _socket(0), _fds(NULL)
{
}
Server::~Server() {}

std::string Server::dateString()
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    return (dt);
}

void Server::run()
{
    int opt = 1; // setsockopt option
    
    if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
    {
        std::cerr << "setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    this->setNonBlocking(_socket);
    // Set up the server address structure for IPv4
    _client_address.sin_family = AF_INET;
    _client_address.sin_addr.s_addr = INADDR_ANY;
    _client_address.sin_port = htons(_port);
    
    if (bind(_socket, (struct sockaddr *)&_client_address, sizeof(_client_address)) < 0)
    {
        std::cerr << "bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(_socket, 64) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Server is listening on port " << _port << " and waiting for connections..." << std::endl;
    constructDescriptorSet();
    while (1)
    {
        int poll_count = poll(_fds, _users.size() + 1, -1);
        if (poll_count < 0)
        {
            std::cerr << "poll failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < _users.size() + 1; i++)
        {
            if (_fds[i].revents == 0)
                continue;
            if (_fds[i].fd == _socket)
                this->acceptNewConnection();
            else if (i > 0)
            {
                Client *client = _users[i - 1];
                this->readFromClient(client);
            }
        }
    }
}

void Server::setNonBlocking(int fd)
{
    int flags;
    
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        std::cerr << "fcntl failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    flags |= O_NONBLOCK;
    int s = fcntl(fd, F_SETFL, flags);
    if (s == -1)
    {
        std::cerr << "fcntl failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Server::constructDescriptorSet()
{
    // Create a single pollfd for handling all operations
    if (this->_fds)
        delete[] this->_fds;
    this->_fds = new struct pollfd[this->_users.size() + 1];
    this->_fds[0].fd = this->_socket;
    this->_fds[0].events = POLLIN;
    for (size_t i = 0; i < this->_users.size(); i++)
    {
        this->_fds[i + 1].fd = this->_users[i]->getFd();
        this->_fds[i + 1].events = POLLIN;
    }
}

void Server::acceptNewConnection()
{
    int socket;
    
    while (1)
    {
        socklen_t address_len = sizeof(_client_address);
        struct sockaddr_in address;
        socket = accept(_socket, (struct sockaddr *)&address, &address_len);
        if (socket < 0)
        {
            if (errno != EWOULDBLOCK)
                std::cerr << "Error: Failed to accept connection." << std::endl;
            break;
        }
        std::string ip = inet_ntoa(address.sin_addr);
        int port = ntohs(address.sin_port);
        if (ip.empty() || ip == "1")
            ip = "127.0.0.1";
        this->_users.push_back(new Client(ip, this, port, socket)); // add new client to the list
        this->setNonBlocking(socket); // set the socket to non-blocking
        this->constructDescriptorSet(); // update the descriptor set
        std::cout << "New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    }
}


void Server::readFromClient(Client *client)
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read = recv(client->getFd(), buffer, BUFFER_SIZE, 0);
    if (bytes_read < 0)
    {
        std::cerr << "recv failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (bytes_read == 0)
    {
        std::cout << "Connection closed by " << client->getHostname() << std::endl;
        this->removeClient(client->getFd());
    }
    else
    {
        buffer[bytes_read] = '\0';
        std::cout << "Received: " << buffer;
    }
}

void Server::removeClient(int fd)
{
    for (size_t i = 0; i < this->_users.size(); i++)
    {
        if (this->_users[i]->getFd() == fd)
        {
            delete this->_users[i];
            this->_users.erase(this->_users.begin() + i);
            break;
        }
    }
}
