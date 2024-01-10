/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:10:58 by ataouaf           #+#    #+#             */
/*   Updated: 2024/01/10 11:55:45 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

Client::Client(std::string& host, Server *server, int port, int fd) : _hostname(host), _password(0), _port(port), _fd(fd), _server(server) {(void)_server;}

Client::~Client() {}

void Client::setMessage(std::string message) { _message = message; }

void Client::setNickname(std::string nickname) { _nickname = nickname; }

void Client::setUsername(std::string username) { _username = username; }

void Client::setRealname(std::string realname) { _realname = realname; }

void Client::setServername(std::string servername) { _servername = servername; }

void Client::setHostname(std::string hostname) { _hostname = hostname; }

void Client::setPassword(int password) { _password = password; }

void Client::setPort(int port) { _port = port; }

void Client::setFd(int fd) { _fd = fd; }

std::string const& Client::getMessage() const { return (_message); }

std::string const& Client::getNickname() const { return (_nickname); }

std::string const& Client::getUsername() const { return (_username); }

std::string const& Client::getRealname() const { return (_realname); }

std::string const& Client::getServername() const { return (_servername); }

std::string const& Client::getHostname() const { return (_hostname); }

int Client::getPassword() const { return (_password); }

int Client::getPort() const { return (_port); }

int Client::getFd() const { return (_fd); }

std::vector<std::string> Client::split(std::string str, char c)
{
    std::vector<std::string> res;
    std::string tmp;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == c)
        {
            res.push_back(tmp);
            tmp.clear();
        }
        else
            tmp += str[i];
    }
    res.push_back(tmp);
    return (res);
}


void Client::welcome()
{
    std::string welcome = "Welcome to the Internet Relay Network " + this->getNickname() + "!" + this->getUsername() + "@" + this->getHostname();
    this->setMessage(welcome);
    this->sendMessage();
}

void Client::reply(std::string message)
{
    this->setMessage(message);
    this->sendMessage();
}

void Client::reply(std::string message, std::string message2)
{
    std::string msg = message + " " + message2;
    this->setMessage(msg);
    this->sendMessage();
}

void Client::sendMessage()
{
    std::string msg = this->getMessage();
    if (msg.empty())
        return;
    msg += "\r\n";
    send(this->getFd(), msg.c_str(), msg.length(), 0);
    this->setMessage("");
}

bool Client::isRegistered()
{
    return (this->getNickname().empty() && this->getUsername().empty() && this->getRealname().empty() && this->_password == 0);
}