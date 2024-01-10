/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 05:00:32 by ataouaf           #+#    #+#             */
/*   Updated: 2024/01/10 11:24:15 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

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

#include "Client.hpp"
#include "Server.hpp"

class Client;
class Server;

class Command
{
    public:
        std::map<std::string, Command *> _commands;
        Command();
        ~Command();
        void execute(Client *client, std::string command);
        
};



#endif