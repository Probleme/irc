/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:47 by ataouaf           #+#    #+#             */
/*   Updated: 2024/01/10 11:37:58 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <poll.h>
#include <fcntl.h>
#include <unistd.h>
# include <sys/types.h>

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

class Server;

class Client{
    private:
        std::string _servername;
        std::string _hostname;
        std::string _realname;
        std::string _username;
        std::string _nickname;
        std::string _message;
        int _password;
        int _port;
        int _fd;
        Server *_server;
    public:
        Client(std::string& host, Server *server, int port, int fd);
        ~Client();
        void setMessage(std::string message);
        void setNickname(std::string nickname);
        void setUsername(std::string username);
        void setRealname(std::string realname);
        void setServername(std::string servername);
        void setHostname(std::string hostname);
        void setPassword(int password);
        void setPort(int port);
        void setFd(int fd);
        std::string const& getMessage() const;
        std::string const& getNickname() const;
        std::string const& getUsername() const;
        std::string const& getRealname() const;
        std::string const& getServername() const;
        std::string const& getHostname() const;
        int getPassword() const;
        int getPort() const;
        int getFd() const;
        
        bool isRegistered();
        void welcome();
        void reply(std::string message);
        void reply(std::string message, std::string message2);
        void sendMessage();
        
        std::vector<std::string> split(std::string str, char c);

        
};

#endif